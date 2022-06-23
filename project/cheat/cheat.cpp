//
// Created by Liga on 6/21/2022.
//

#include "cheat.hpp"
#include "../entry.hpp"

#include "helpers/console/console.hpp"
#include "hooks/hooks.hpp"

void cheat::impl::init( )
{
	console::init( );
	g_hooks.init( );

	while ( !GetAsyncKeyState( VK_DELETE ) ) {
		Sleep( 15 );
	}

	cheat::impl::shutdown( );
}

void cheat::impl::shutdown( )
{
	free_library_and_exit_thread( g_entry.module_handle, 0 );
}
