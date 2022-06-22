#include "hooks.h"
#include "../sdk/interfaces/interfaces.h"
#include "../../common.h"

bool h::init( )
{
	SEH_START

		if ( MH_Initialize( ) != MH_OK )
			throw std::runtime_error( _( "[hotwheels] - error - failed initialize minhook" ) );

	if ( detours::alloc_key_values_memory.install( mem::get_vfunc( i::key_values_system, 1 ), h::alloc_key_values_memory ) )
		logging::print( _( "[hotwheels] - success - hooked alloc_key_values_memory" ) );

	if ( detours::create_move_proxy.install( mem::get_vfunc( i::client, 22 ), h::create_move_proxy ) )
		logging::print( _( "[hotwheels] - success - hooked create_move" ) );

	if ( detours::frame_stage_notify.install( mem::get_vfunc( i::client, 37 ), h::frame_stage_notify ) )
		logging::print( _( "[hotwheels] - success - hooked frame_stage_notify" ) );

	if ( detours::draw_print_text.install( mem::get_vfunc( i::surface, 28 ), h::draw_print_text ) )
		logging::print( _( "[hotwheels] - success - hooked draw_print_text" ) );

	if ( detours::draw_model_execute.install( mem::get_vfunc( i::model_render, 21 ), h::draw_model_execute ) )
		logging::print( _( "[hotwheels] - success - hooked draw_model_execute" ) );

	if ( detours::push_notice.install( reinterpret_cast< void* >( mem::relative_to_absolute( mem::pattern_scan( _( "client.dll" ), _( "E8 ? ? ? ? 83 7D D4 00 7C 22" ) ) + 0x1 ) ), h::push_notice ) )
		logging::print( _( "[hotwheels] - success - hooked push_notice" ) );

	if ( detours::vsnprintf.install( reinterpret_cast< void* >( mem::pattern_scan( _( "client.dll" ), _( "55 8B EC 51 56 8B 75 0C 8D 45 14 57 8B 7D 08 8B D6 50 51 FF 75 10 8B CF E8 ? ? ? ? 83 C4 0C 85 C0 78 08 85 F6 7E 0C 3B C6 7C 08 8D 46 FF" ) ) ), h::vsnprintf ) )
		logging::print( _( "[hotwheels] - success - hooked vsnprintf" ) );

	if ( detours::lock_cursor.install( mem::get_vfunc( i::surface, 67 ), h::lock_cursor ) )
		logging::print( _( "[hotwheels] - success - hooked lock_cursor" ) );	

	if ( detours::reset.install( mem::get_vfunc( i::direct_device, 16 ), h::reset ) )
		logging::print( _( "[hotwheels] - success - hooked reset" ) );

	if ( detours::end_scene.install( mem::get_vfunc( i::direct_device, 42 ), h::end_scene ) )
		logging::print( _( "[hotwheels] - success - hooked end_scene" ) );

	return true;

	SEH_END

		return false;
}

void h::revert( )
{
	MH_DisableHook( MH_ALL_HOOKS );
	MH_RemoveHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}