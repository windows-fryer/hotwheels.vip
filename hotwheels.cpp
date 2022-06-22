#include <thread>
#include <include/discord_rpc.h>

#include "common.h"
#include "core/gui/gui.h"
#include "core/cfg/config.h"
#include "core/hooks/hooks.h"
#include "core/props/props.h"
#include "core/sdk/interfaces/interfaces.h"

DWORD WINAPI init( LPVOID param )
{
	try
	{
		while ( mem::get_module_base_handle( _( "serverbrowser.dll" ) ) == nullptr )
			std::this_thread::sleep_for( 200ms );

#ifdef _DEBUG
		if ( !logging::attach( _( "hotwheels | developer's console" ) ) )
			throw std::runtime_error( _( "[hotwheels] - error - failed to allocated console" ) );

		logging::print( _( "[hotwheels] - success - console allocated" ) );
#endif

		if ( !i::init( ) )
			throw std::runtime_error( _( "[hotwheels] - error - falied to capture interfaces" ) );

		logging::print( _( "[hotwheels] - success - interfaces captured" ) );

		if ( !c_netvar_manager::get( )->init( ) )
			throw std::runtime_error( _( "[hotwheels] - error - falied to initialise netvar manager" ) );

		logging::print( _( "[hotwheels] - success - initialised netvar manager" ) );

		if ( !gui::input::init( ) )
			throw std::runtime_error( _( "[hotwheels] - error - falied to initialise gui input" ) );

		logging::print( _( "[hotwheels] - success - initialised gui input" ) );

		if ( !h::init( ) )
			throw std::runtime_error( _( "[hotwheels] - error - falied to initialise hooks" ) );

		logging::print( _( "[hotwheels] - success - initialised hooks" ) );

		if ( !c::init( ) )
			throw std::runtime_error( _( "[hotwheels] - error - falied to initialise config system" ) );

		logging::print( _( "[hotwheels] - success - initialised config system" ) );
	}
	catch ( const std::exception& ex )
	{
		logging::push_console_color( FOREGROUND_INTENSE_RED );
		logging::print( _( "[hotwheels] - error - {}" ), ex.what( ) );
		logging::pop_console_color( );

#ifdef _DEBUG
		_RPT0( _CRT_ERROR, ex.what( ) );
#else
		LI_FN( FreeLibraryAndExitThread )( static_cast< HMODULE >( param ), EXIT_FAILURE );
#endif
	}
	return 1UL;
}

DWORD WINAPI revert( LPVOID param )
{
	while ( !LI_FN( GetAsyncKeyState )( VK_END ) )
		std::this_thread::sleep_for( 500ms );

	if ( gui::g_data.m_opened )
		gui::g_data.m_opened = false;

	if ( c::get<bool>( vars.misc_discord_rpc ) )
	{
		Discord_ClearPresence( );
		Discord_Shutdown( );
	}

	h::revert( );

	gui::input::revert( );

	gui::revert( );

#ifdef _DEBUG
	logging::detach( );
#endif

	LI_FN( FreeLibraryAndExitThread )( ( HMODULE ) param, 0 );

	return 0;
}

BOOL APIENTRY DllMain( HMODULE module, DWORD reason_to_call, LPVOID reserved )
{
	if ( reason_to_call == DLL_PROCESS_ATTACH )
	{
		LI_FN( DisableThreadLibraryCalls )( module );

		if ( auto thread = LI_FN( CreateThread )( nullptr, 0U, init, module, 0UL, nullptr ); thread != nullptr )
			LI_FN( CloseHandle )( thread );

#ifdef _DEBUG
		if ( auto thread = LI_FN( CreateThread )( nullptr, 0U, revert, module, 0UL, nullptr ); thread != nullptr )
			LI_FN( CloseHandle )( thread );
#endif

		return TRUE;
	}

	return FALSE;
}