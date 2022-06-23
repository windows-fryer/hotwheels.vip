//
// Created by Liga on 6/21/2022.
//

#include "entry.hpp"
#include "cheat/cheat.hpp"
#include "cheat/helpers/console/console.hpp"
#include "cheat/hooks/hooks.hpp"

using namespace entry;

void impl::init( )
{
	auto thread_handle = create_thread( g_cheat.init );

	if ( thread_handle )
		close_handle( thread_handle );
}

void impl::shutdown( )
{
	g_hooks.shutdown( );
	console::shutdown( );
}

bool win_api dll_main( hinstance module_handle, std::uintptr_t reason_for_call, void* reserved )
{
	disable_thread_library_calls( module_handle );

	g_entry.module_handle = module_handle;

	if ( reason_for_call == DLL_PROCESS_ATTACH ) {
		g_entry.init( );
	}

	if ( reason_for_call == DLL_PROCESS_DETACH ) {
		g_entry.shutdown( );
	}

	return true;
}