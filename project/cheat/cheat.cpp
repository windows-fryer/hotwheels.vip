//
// Created by liga on 7/1/2022.
//

#include "cheat.hpp"

#include "features/overlay/overlay.hpp"
#include "helpers/configs/config.hpp"
#include "helpers/driver/driver.hpp"

#include "features/aimbot/aimbot.hpp"
#include "features/movement/movement.hpp"

#include <Windows.h>
#include <iostream>

void cheat::init( )
{
	// Config stuff
	g_config.insert( "menu_open_smooth", true );

	g_config.insert( "aimbot_rcs", false );
	g_config.insert( "aimbot_rcs_x", 100.f );
	g_config.insert( "aimbot_rcs_y", 100.f );
	g_config.insert( "aimbot_rcs_smooth", 0.f );
	g_config.insert( "aimbot_rcs_error", true );

	g_config.insert( "visuals_boxes", false );
	g_config.insert( "visuals_boxes_color", ImVec4( 1.f, 1.f, 1.f, 1.f ) );

	g_config.insert( "visuals_recoil_crosshair", false );
	g_config.insert( "visuals_recoil_crosshair_color", ImVec4( 1.f, 1.f, 1.f, 1.f ) );

	g_config.insert( "movement_bunny_hop", false );

	// Actually important threadsafe operations
	DWORD process_id{ };

	GetWindowThreadProcessId( FindWindow( "Valve001", NULL ), &process_id );

	while ( !process_id ) {
		GetWindowThreadProcessId( FindWindow( "Valve001", NULL ), &process_id );

		Sleep( 10 );
	}

	driver::init( reinterpret_cast< HANDLE >( process_id ) );

	// Fuck off operations
	CreateThread( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( overlay::init ), nullptr, 0, nullptr );
	CreateThread( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( movement::routine ), nullptr, 0, nullptr );
	CreateThread( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( aimbot::routine ), nullptr, 0, nullptr );

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