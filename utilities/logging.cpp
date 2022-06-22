#include "logging.h"

bool logging::attach( const char* console_title )
{
	if ( !AllocConsole( ) )
		return false;

	AttachConsole( ATTACH_PARENT_PROCESS );

	if ( freopen_s( &stream, _( "CONOUT$" ), _( "w" ), stdout ) != 0 )
		return false;

	if ( !SetConsoleTitle( console_title ) )
		return false;

	return true;
}

void logging::detach( )
{
	fclose( stream );

	FreeConsole( );

	if ( const auto console_window = GetConsoleWindow( ); console_window != nullptr )
		PostMessageW( console_window, WM_CLOSE, 0U, 0L );
}