#ifndef WEDNESDAY_WTF_CONSOLE_HPP
#define WEDNESDAY_WTF_CONSOLE_HPP

#include "../../../dependencies/fmt/core.h"

#include <Windows.h>
#include <iostream>
#include <string>

namespace console
{
	namespace color
	{
		void blue( );

		void red( );

		void green( );

		void yellow( );

		void white( );

		void cyan( );

		void purple( );

		void grey( );
	} // namespace color

	void init( );
	void shutdown( );

	inline FILE *con_out, *con_in;

	template< typename... ARGS >
	void log( fmt::string_view message, ARGS&&... arguments )
	{
		fmt::string_view formatted_string = fmt::vformat( message.data( ), fmt::make_format_args( arguments... ) );

		std::cout << std::string( formatted_string );
	}
} // namespace console

#endif // WEDNESDAY_WTF_CONSOLE_HPP
