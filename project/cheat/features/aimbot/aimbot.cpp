//
// Created by liga on 7/5/2022.
//

#include "aimbot.hpp"

#include "../../cheat.hpp"

#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"

#include "../../sdk/enums/flags.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../../sdk/structs/vector.hpp"

void aimbot::routine( )
{
	static auto client_dll = driver::base_address( "client.dll" );
	static auto engine_dll = driver::base_address( "engine.dll" );
	static sdk::vector last_aim_punch{ };

	while ( true ) {
		auto player = sdk::game::local_player( );

		if ( !player )
			continue;

		auto client_state = driver::read< std::uint32_t >( reinterpret_cast< void* >( engine_dll + offsets::client_state ) );
		auto view_angles  = driver::read< sdk::vector >( reinterpret_cast< PVOID >( client_state + offsets::view_angles ) );
		auto aim_punch    = player->aim_punch_angle( );

		sdk::vector adjusted_angles = { aim_punch.x * ( *g_config.find< float >( "aimbot_rcs_y" ) / 100.f ),
			                            aim_punch.y * ( *g_config.find< float >( "aimbot_rcs_x" ) / 100.f ) };

		if ( GetAsyncKeyState( VK_LBUTTON ) ) {
			sdk::vector random_angles = { static_cast< float >( rand( ) * 1000 % 10 ) / 10, static_cast< float >( rand( ) * 1000 % 10 ) / 10.f };

			if ( *g_config.find< bool >( "aimbot_rcs" ) ) {
				auto corrected_angle = view_angles - ( adjusted_angles * 2 - last_aim_punch ) +
				                       ( *g_config.find< bool >( "aimbot_rcs_error" ) ? random_angles : sdk::vector{ } );

				auto lerped_angle = view_angles.lerp( corrected_angle, -( *g_config.find< float >( "aimbot_rcs_smooth" ) / 100.f ) + 1.f );

				driver::write< sdk::vector >( reinterpret_cast< PVOID >( client_state + offsets::view_angles ), lerped_angle );
			}
		}

		last_aim_punch = adjusted_angles * 2;

		Sleep( 1 );
	}
}