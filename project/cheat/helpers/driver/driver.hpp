//
// Created by liga on 7/2/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_DRIVER_HPP
#define HOTWHEELS_CSGO_EXTERNAL_DRIVER_HPP

#define NOMINMAX

#include <Windows.h>
#include <iostream>
#include <string_view>

struct READ_MEMORY_CALLBACK_INPUT {
	HANDLE pid;
	PVOID address;
	SIZE_T size;

	PVOID memory_pointer;
};

struct WRITE_MEMORY_CALLBACK_INPUT {
	HANDLE pid;
	PVOID address;
	SIZE_T size;

	PVOID memory_pointer;
};

struct BASE_ADDRESS_CALLBACK_INPUT {
	HANDLE pid;
	WCHAR module[ 0x256 ];

	ULONG64 response;
};

constexpr int IOCTL_WRITE_MEMORY = CTL_CODE( FILE_DEVICE_UNKNOWN, ( 0x800 + 2 ), METHOD_BUFFERED, FILE_SPECIAL_ACCESS );
constexpr int IOCTL_READ_MEMORY  = CTL_CODE( FILE_DEVICE_UNKNOWN, ( 0x800 + 3 ), METHOD_BUFFERED, FILE_SPECIAL_ACCESS );
constexpr int IOCTL_BASE_ADDRESS = CTL_CODE( FILE_DEVICE_UNKNOWN, ( 0x800 + 4 ), METHOD_BUFFERED, FILE_SPECIAL_ACCESS );

namespace driver
{
	inline HANDLE device_handle{ };
	inline HANDLE process_pid{ };

	bool init( HANDLE pid );
	bool shutdown( );

	template< typename T >
	inline T read( PVOID address )
	{
		READ_MEMORY_CALLBACK_INPUT read_memory_callback_input{ };
		DWORD bytes_returned{ };

		T temporary_memory{ };

		read_memory_callback_input.memory_pointer = &temporary_memory;
		read_memory_callback_input.pid            = process_pid;
		read_memory_callback_input.address        = reinterpret_cast< PVOID >( address );
		read_memory_callback_input.size           = sizeof( T );

		DeviceIoControl( device_handle, IOCTL_READ_MEMORY, &read_memory_callback_input, sizeof( read_memory_callback_input ),
		                 &read_memory_callback_input, sizeof( read_memory_callback_input ), &bytes_returned, nullptr );

		return temporary_memory;
	}

	template< typename T >
	inline bool write( void* address, T value )
	{
		WRITE_MEMORY_CALLBACK_INPUT write_memory_callback_input{ };
		DWORD bytes_returned{ };

		T written_value = value;

		write_memory_callback_input.pid            = process_pid;
		write_memory_callback_input.address        = reinterpret_cast< PVOID >( address );
		write_memory_callback_input.size           = sizeof( T );
		write_memory_callback_input.memory_pointer = &written_value;

		return DeviceIoControl( device_handle, IOCTL_WRITE_MEMORY, &write_memory_callback_input, sizeof( write_memory_callback_input ), nullptr, 0,
		                        &bytes_returned, nullptr );
	}

	inline std::uint64_t base_address( const char* name )
	{
		BASE_ADDRESS_CALLBACK_INPUT base_address_callback_input{ };
		DWORD bytes_returned{ };

		int length_wchar = MultiByteToWideChar( CP_UTF8, 0, name, -1, nullptr, 0 );
		MultiByteToWideChar( CP_UTF8, 0, name, -1, base_address_callback_input.module, length_wchar );

		base_address_callback_input.pid = process_pid;

		DeviceIoControl( device_handle, IOCTL_BASE_ADDRESS, &base_address_callback_input, sizeof( base_address_callback_input ),
		                 &base_address_callback_input, sizeof( base_address_callback_input ), &bytes_returned, nullptr );

		return base_address_callback_input.response;
	}
} // namespace driver

#endif // HOTWHEELS_CSGO_EXTERNAL_DRIVER_HPP
