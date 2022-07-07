//
// Created by liga on 7/2/2022.
//

#include "driver.hpp"

#include <iostream>

bool driver::init( HANDLE pid )
{
	if ( !device_handle ) {
		device_handle = CreateFile( "\\\\.\\hotwheels", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );

		if ( device_handle == INVALID_HANDLE_VALUE ) {
			std::cout << "Driver failure. " << std::hex << GetLastError( ) << std::endl;
		} else {
			std::cout << "Driver success." << std::endl;
		}
	}

	process_pid = pid;

	return true;
}

bool driver::shutdown( )
{
	if ( device_handle != INVALID_HANDLE_VALUE ) {
		CloseHandle( device_handle );
		device_handle = INVALID_HANDLE_VALUE;
	}

	return true;
}