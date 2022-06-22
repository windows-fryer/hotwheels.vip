#include <Windows.h>

#include "../../global/snakeify.hpp"
#include "console.hpp"

//-----------------------------------------------------------------------------
// @PURPOSE : Allocates a console for reading & writing.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::init( )
{
	if ( !AllocConsole( ) ) {
		// todo: assert shit instead.
		return;
	}

	freopen_s( &con_out, "CONIN$", "w", stdin );
	freopen_s( &con_in, "CONOUT$", "w", stdout );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Closes console's read & write handles.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::shutdown( )
{
	fclose( con_out );
	fclose( con_in );

	free_console( );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color blue.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::blue( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color red.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::red( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_RED | FOREGROUND_INTENSITY );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color green.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::green( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color yellow.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::yellow( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color white.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::white( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color cyan.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::cyan( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_GREEN | FOREGROUND_BLUE );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color purple.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::purple( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_RED | FOREGROUND_BLUE );
}

//-----------------------------------------------------------------------------
// @PURPOSE : Turns the console to the color grey.
// @INPUT   : No arguments.
//-----------------------------------------------------------------------------
void console::color::grey( )
{
	HANDLE handle = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( handle, FOREGROUND_INTENSITY );
}