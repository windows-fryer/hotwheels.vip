//
// Created by liga on 7/3/2022.
//

#include <Windows.h>

#include "movement.hpp"

#include "../../cheat.hpp"
#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"
#include "../../sdk/enums/flags.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../../sdk/structs/vector.hpp"

void movement::routine( )
{
	static auto client_dll    = driver::base_address( "client.dll" );
	static auto engine_dll    = driver::base_address( "engine.dll" );
	static auto window_handle = FindWindowA( "Valve001", nullptr );

	while ( !cheat::requested_shutdown ) {
		if ( *g_config.find< bool >( "movement_bunny_hop" ) ) {
			if ( GetAsyncKeyState( VK_SPACE ) && GetForegroundWindow( ) == window_handle ) {
				auto player = sdk::game::local_player( );
				auto flags  = player->flags( );

				if ( flags & sdk::ONGROUND ) {
					driver::write< int >( reinterpret_cast< void* >( client_dll + offsets::force_jump ), 5 );
				} else {
					driver::write< int >( reinterpret_cast< void* >( client_dll + offsets::force_jump ), 4 );
				}
			}
		}

		Sleep( 1 );
	}
}