#pragma once
#include <format>
#include <fstream>
#include <iostream>

#include "../common.h"
#include "encryption/xorstr.h"

#define FOREGROUND_WHITE		    (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		    0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)

#ifdef _DEBUG
#define SEH_CATCH _RPT0(_CRT_ERROR, ex.what());
#else
#define SEH_CATCH std::abort();
#endif

#define SEH_START try {
#define SEH_END } catch (const std::exception& ex) {	\
	logging::push_console_color(FOREGROUND_INTENSE_RED);		\
	logging::print(_("[hotwheels] - error - {}"), ex.what());			\
	logging::pop_console_color();								\
	SEH_CATCH }
#pragma endregion

namespace logging
{
	inline FILE* stream;
	inline std::uint16_t console_color = FOREGROUND_WHITE;

	bool attach( const char* console_title );
	void detach( );

	template <typename ... Args_t>
	void print( const std::string_view text, const Args_t& ... arg_list )
	{
		const std::string time = std::vformat( _( "[{:%d-%m-%Y %X}] " ), std::make_format_args( std::chrono::system_clock::now( ) ) );

#ifdef _DEBUG
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_INTENSE_BLUE );
		std::cout << time;
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), console_color );
		if constexpr ( sizeof...( arg_list ) > 0 )
			std::cout << std::vformat( text, std::make_format_args( arg_list... ) ) << std::endl;
		else
			std::cout << text << std::endl;
#endif
	}

	inline void push_console_color( const std::uint16_t new_color )
	{
		console_color = new_color;
	}

	inline void pop_console_color( )
	{
		console_color = FOREGROUND_WHITE;
	}
}
