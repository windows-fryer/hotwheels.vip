#define _CRT_SECURE_NO_WARNINGS

#include "../../hooks.h"
#include "../../../cfg/config.h"

int __cdecl h::vsnprintf( char* text, int text_length, const char* fmt, ... )
{
	int v4 = { };

	va_list args;
	va_start( args, fmt );

	if ( c::get<bool>( vars.custom_netgraph ) )
	{
		if ( strstr( fmt, _( "fps:" ) ) ) {
			fmt = _( "fps: %5i / var: %4.1f ms" );
			v4 = _vsnprintf( text, text_length, fmt, args );
		}
		else if ( strstr( fmt, _( "loss:" ) ) ) {
			fmt = _( "lost: %3i%% / chocked: %2i%%" );
			v4 = _vsnprintf( text, text_length, fmt, args );
		}
		else if ( strstr( fmt, _( "tick:" ) ) ) {
			fmt = _( "tick:%5.1f / " );
			v4 = _vsnprintf( text, text_length, fmt, args );
		}
		else if ( strstr( fmt, _( "sv:" ) ) ) {
			fmt = _( "sv:%5.1f %s%4.1f ms" );
			v4 = _vsnprintf( text, text_length, fmt, args );
		}
		else
			v4 = _vsnprintf( text, text_length, fmt, args );
	}
	else
		v4 = _vsnprintf( text, text_length, fmt, args );

	va_end( args );

	if ( ( v4 < 0 ) || ( text_length > 0 && v4 >= text_length ) )
	{
		v4 = text_length - 1;
		text[ text_length - 1 ] = '\0';
	}

	return v4;
}