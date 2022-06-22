#include "../../hooks.h"
#include "../../../cfg/config.h"
#include "../../../sdk/interfaces/interfaces.h"

void __fastcall h::draw_print_text( int ecx, int edx, const wchar_t* text, int text_length, int draw_type )
{
	static auto original = detours::draw_print_text.get_original<decltype( &h::draw_print_text )>( );

	if ( !c::get<bool>( vars.custom_netgraph ) )
		return original( ecx, edx, text, text_length, draw_type );

    if ( wcsncmp( text, _( L"fps" ), 3 ) == 0 ) 
    {
        i::surface->set_text_color( c::get<color>( vars.color_custom_netgraph ).base<color_r>() * 255, c::get<color>( vars.color_custom_netgraph ).base<color_g>( ) * 255, c::get<color>( vars.color_custom_netgraph ).base<color_b>( ) * 255, c::get<color>( vars.color_custom_netgraph ).base<color_a>( ) * 255 );

        const auto new_text = std::wstring( _( L"[hotwheels] " ) );
        original( ecx, edx, new_text.data( ), new_text.length( ), draw_type );

        i::surface->set_text_color( 229, 229, 178, 255 );
        return original( ecx, edx, text, text_length, draw_type );
    }

    return original( ecx, edx, text, text_length, draw_type );
}