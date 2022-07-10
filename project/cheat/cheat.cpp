//
// Created by liga on 7/1/2022.
//

#include "cheat.hpp"

#include "features/overlay/overlay.hpp"
#include "helpers/configs/config.hpp"
#include "helpers/driver/driver.hpp"

#include "features/aimbot/aimbot.hpp"
#include "features/changer/changer.hpp"
#include "features/movement/movement.hpp"

#include <chrono>
#include <thread>

void cheat::init( )
{
	g_config.init( );

	HANDLE process_id{ };

	while ( !process_id ) {
		GetWindowThreadProcessId( FindWindow( "Valve001", nullptr ), reinterpret_cast< LPDWORD >( &process_id ) );

		if ( process_id )
			break;

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
	}

	driver::init( process_id );

	// Fuck off operations
	create_thread( overlay::init );
	create_thread( movement::routine );
	create_thread( aimbot::routine );
	create_thread( changer::routine );

	while ( !GetAsyncKeyState( VK_DELETE ) ) {
		Sleep( 10 );
	}

	cheat::shutdown( );
}

void cheat::shutdown( )
{
	// Basically not needed, why free memory when windows do it for us 😊

	requested_shutdown = true;
}