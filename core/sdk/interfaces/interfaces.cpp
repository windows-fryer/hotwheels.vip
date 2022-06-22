#include "interfaces.h"

#include "../../../common.h"

bool i::init( )
{
	client = capture<i_base_client_dll>( _( "client.dll" ), _( "VClient" ) );
	if ( client == nullptr )
		return false;

	surface = capture<i_surface>( _( "vguimatsurface.dll" ), _( "VGUI_Surface" ) );
	if ( surface == nullptr )
		return false;

	input_system = capture<i_input_system>( _( "inputsystem.dll" ), _( "InputSystemVersion" ) );
	if ( input_system == nullptr )
		return false;

	engine_client = capture<i_engine_client>( _( "engine.dll" ), _( "VEngineClient" ) );
	if ( engine_client == nullptr )
		return false;

	client_entity_list = capture<i_client_entity_list>( _( "client.dll" ), _( "VClientEntityList" ) );
	if ( client_entity_list == nullptr )
		return false;

	model_render = capture<i_model_render>( _( "engine.dll" ), _( "VEngineModel" ) );
	if ( model_render == nullptr )
		return false;

	material_system = capture<i_material_system>( _( "materialsystem.dll" ), _( "VMaterialSystem" ) );
	if ( material_system == nullptr )
		return false;

	file_system = capture<void>( _( "filesystem_stdio.dll" ), _( "VBaseFileSystem" ) );
	if ( file_system == nullptr )
		return false;

	client_mode = **reinterpret_cast< i_client_mode_shared*** >( mem::get_vfunc<std::uintptr_t>( client, 10 ) + 0x5 );
	if ( client_mode == nullptr )
		return false;

	logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), _( "IClientModeShared" ), reinterpret_cast< std::uintptr_t >( client_mode ) );

	client_state = **reinterpret_cast< i_client_state*** >( mem::pattern_scan( _( "engine.dll" ), _( "A1 ? ? ? ? 8B 88 ? ? ? ? 85 C9 75 07" ) ) + 0x1 );
	if ( client_state == nullptr )
		return false;

	logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), _( "IClientState" ), reinterpret_cast< std::uintptr_t >( client_state ) );

	globals = **reinterpret_cast< i_global_vars_base*** >( mem::get_vfunc<std::uintptr_t>( client, 11 ) + 0xA );
	if ( globals == nullptr )
		return false;

	logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), _( "IGlobalVarsBase" ), reinterpret_cast< std::uintptr_t >( globals ) );

	input = *reinterpret_cast< i_input** >( mem::pattern_scan( _( "client.dll" ), _( "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) ) + 0x1 );
	if ( input == nullptr )
		return false;

	logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), _( "IInput" ), reinterpret_cast< std::uintptr_t >( input ) );

	direct_device = **reinterpret_cast< IDirect3DDevice9*** >( mem::pattern_scan( _( "shaderapidx9.dll" ), _( "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) ) + 0x1 );
	if ( direct_device == nullptr )
		return false;

	logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), _( "IDirect3DDevice9" ), reinterpret_cast< std::uintptr_t >( direct_device ) );

	key_values_system = reinterpret_cast< key_values_system_fn >( mem::get_export_address( mem::get_module_base_handle( _( "vstdlib.dll" ) ), _( "KeyValuesSystem" ) ) )( );
	if ( key_values_system == nullptr )
		return false;

	logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), _( "IKeyValuesSystem" ), reinterpret_cast< std::uintptr_t >( key_values_system ) );

	return true;
}

template <typename T>
T* i::capture( const std::string_view module_name, const std::string_view interface_name )
{
	const auto get_register_list = [ &module_name ]( ) -> c_interface_register*
	{
		void* original_fn = nullptr;

		if ( const auto module_handle = mem::get_module_base_handle( module_name ); module_handle != nullptr )
			original_fn = mem::get_export_address( module_handle, _( "CreateInterface" ) );

		if ( original_fn == nullptr )
			throw std::runtime_error( _( "[hotwheels] - error - failed get createinterface address" ) );

		const std::uintptr_t create_interface_relative = reinterpret_cast< std::uintptr_t >( original_fn ) + 0x5;
		const std::uintptr_t create_interface = create_interface_relative + 4U + *reinterpret_cast< std::int32_t* >( create_interface_relative );
		return **reinterpret_cast< c_interface_register*** >( create_interface + 0x6 );
	};

	for ( auto reg = get_register_list( ); reg != nullptr; reg = reg->m_next )
	{
		if ( ( std::string_view( reg->m_name ).compare( 0U, interface_name.length( ), interface_name ) == 0 &&
			std::atoi( reg->m_name + interface_name.length( ) ) > 0 ) ||
			interface_name.compare( reg->m_name ) == 0 )
		{
			auto interface_address = reg->m_create_fn( );

			logging::print( _( "[hotwheels] - success - captured {} interface -> {:#08X}" ), reg->m_name, reinterpret_cast< std::uintptr_t >( interface_address ) );

			return static_cast< T* >( interface_address );
		}
	}

#ifdef _DEBUG
	logging::push_console_color( FOREGROUND_INTENSE_RED );
	logging::print( _( "[hotwheels] - error - failed to find interface \"{}\" in \"{}\"" ), interface_name, module_name );
	logging::pop_console_color( );
#endif

	return nullptr;
}