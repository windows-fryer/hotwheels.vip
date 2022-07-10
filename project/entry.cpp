//
// Created by liga on 7/1/2022.
//

#include "entry.hpp"
#include "cheat/cheat.hpp"

#include <Windows.h>
#include <iostream>

void main_routine( )
{
	cheat::init( );
}

bool win_api dll_main( hinstance module_handle, std::uintptr_t call_reason, void* reserved )
{
	disable_thread_library_calls( module_handle );

	if ( call_reason == DLL_PROCESS_ATTACH ) {
		cheat::module_handle = module_handle;
		
		close_handle( create_thread( main_routine ) );
	}

	return true;
}