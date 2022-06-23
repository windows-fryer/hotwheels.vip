#ifndef HOTWHEELS_BF4_CONSOLE_HPP
#define HOTWHEELS_BF4_CONSOLE_HPP

#include "../../../dependencies/fmt/color.h"
#include "../../../dependencies/fmt/core.h"

#include <Windows.h>
#include <iostream>
#include <string>

namespace console
{
	void init( );
	void shutdown( );

	inline FILE *con_out, *con_in;

	template< fmt::color COLOR = fmt::color::white_smoke, typename... ARGS >
	void log( fmt::string_view message, ARGS&&... arguments )
	{
		HANDLE std_handle = GetStdHandle( STD_OUTPUT_HANDLE );
		DWORD mode        = 0;
		GetConsoleMode( std_handle, &mode );
		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode( std_handle, mode );

		std::string formatted_string = fmt::vformat( message, fmt::make_format_args( arguments... ) );

		fmt::print( fmt::fg( COLOR ), formatted_string  );
	}
} // namespace console

#endif // HOTWHEELS_BF4_CONSOLE_HPP
