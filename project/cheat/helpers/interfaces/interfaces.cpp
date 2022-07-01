//
// Created by liga on 6/29/2022.
//

#include "interfaces.hpp"
#include "../../sdk/include.hpp"
#include "../modules/modules.hpp"
#include "../signature_scan/signature_scan.hpp"

void interfaces::impl::init( )
{
	directx_renderer  = g_game.pattern_scan( "48 8B 0D ? ? ? ? 48 8B 01 FF 50 08 85 C0 75 2D" ).relative( 0x3 ).get< sdk::directx_renderer* >( );
	border_input_node = g_game.pattern_scan( "4C 8B 05 ? ? ? ? 4C 8B 74 24 ? 48 8B 5C 24 ? 49 8B 50 40 48 85 D2 74 16 48 8B 42 10" )
	                        .relative( 0x3 )
	                        .get< sdk::border_input_node* >( );
	client_game_context =
		g_game.pattern_scan( "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B D8 48 89 44 24 ? 4C 8D B6" ).relative( 0x3 ).get< sdk::client_game_context* >( );
}

void interfaces::impl::shutdown( ) { }
