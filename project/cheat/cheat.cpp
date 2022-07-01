//
// Created by Liga on 6/21/2022.
//

#include "cheat.hpp"
#include "../entry.hpp"

#include "helpers/console/console.hpp"
#include "helpers/interfaces/interfaces.hpp"
#include "helpers/modules/modules.hpp"
#include "hooks/hooks.hpp"

void cheat::impl::init( )
{
	modules::init( );
	g_interfaces.init( );
	console::init( );
	hooks::impl::init( );

	while ( !GetAsyncKeyState( VK_DELETE ) ) {
		Sleep( 15 );
	}

	cheat::impl::shutdown( );
}

void cheat::impl::shutdown( )
{
	free_library_and_exit_thread( g_entry.module_handle, 0 );
}
