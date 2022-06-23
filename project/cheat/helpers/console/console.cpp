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