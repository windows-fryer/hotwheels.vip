//
// Created by liga on 7/5/2022.
//

#include "visuals.hpp"

#include "../overlay/overlay.hpp"

#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"

#include "../../helpers/math/math.hpp"
#include "../../sdk/enums/weapon_id.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"

std::pair< ImVec4, bool > calculate_box( sdk::player* player )
{
	static auto engine_dll = driver::base_address( "engine.dll" );

	auto client_state = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::client_state ) );

	sdk::collideable* collideable{ };

	if ( !( collideable = player->collideable( ) ) ) // This is such a chungus burger moment
		return { { }, false };

	sdk::vector mins = collideable->mins( ), maxs = collideable->maxs( );
	sdk::matrix_3x4 transform = player->rgfl( );

	sdk::vector points[] = { sdk::vector( mins.x, mins.y, mins.z ), sdk::vector( mins.x, maxs.y, mins.z ), sdk::vector( maxs.x, maxs.y, mins.z ),
		                     sdk::vector( maxs.x, mins.y, mins.z ), sdk::vector( maxs.x, maxs.y, maxs.z ), sdk::vector( mins.x, maxs.y, maxs.z ),
		                     sdk::vector( mins.x, mins.y, maxs.z ), sdk::vector( maxs.x, mins.y, maxs.z ) };

	sdk::vector translated_points[ 8 ];

	for ( int iterator = 0; iterator < 8; iterator++ )
		translated_points[ iterator ] = math::vector_transform( points[ iterator ], transform );

	sdk::vector screen_points[ 8 ];

	bool on_screen = false;

	for ( int iterator = 0; iterator < 8; iterator++ ) {
		bool buffer_on_screen = true;

		auto return_data = math::world_to_screen( translated_points[ iterator ] );

		screen_points[ iterator ] = return_data.first;
		buffer_on_screen          = return_data.second;

		if ( buffer_on_screen )
			on_screen = true;
	}

	if ( !on_screen )
		return { { }, false };

	float top    = screen_points[ 0 ].y;
	float left   = screen_points[ 0 ].x;
	float right  = screen_points[ 0 ].x;
	float bottom = screen_points[ 0 ].y;

	for ( int iterator = 1; iterator < 8; iterator++ ) {
		if ( left > screen_points[ iterator ].x )
			left = screen_points[ iterator ].x;
		if ( top > screen_points[ iterator ].y )
			top = screen_points[ iterator ].y;
		if ( right < screen_points[ iterator ].x )
			right = screen_points[ iterator ].x;
		if ( bottom < screen_points[ iterator ].y )
			bottom = screen_points[ iterator ].y;
	}

	return { { std::floor( left ), std::floor( top ), std::floor( right ), std::floor( bottom ) }, true };
}

void visuals::routine( )
{
	ImGui::GetBackgroundDrawList( )->Flags &= ~ImDrawListFlags_AntiAliasedLines;

	auto local_player = sdk::game::local_player( );

	if ( !local_player )
		return;

	sdk::vector punch_angle = local_player->aim_punch_angle( );

	if ( *g_config.find< bool >( "visuals_recoil_crosshair" ) && !punch_angle.is_zero( ) ) {
		float x1 = overlay::screen_w / 2.f;
		float y1 = overlay::screen_h / 2.f;

		float x2 = overlay::screen_w / static_cast< float >( local_player->default_fov( ) );
		float y2 = overlay::screen_h / static_cast< float >( local_player->default_fov( ) );

		x1 -= x2 * punch_angle.y;
		y1 += y2 * punch_angle.x;

		x1 = std::floor( x1 );
		y1 = std::floor( y1 );

		ImGui::GetBackgroundDrawList( )->AddLine( ImVec2( x1 - 6, y1 ), ImVec2( x1 + 6, y1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f ) ), 4 );
		ImGui::GetBackgroundDrawList( )->AddLine( ImVec2( x1, y1 - 6 ), ImVec2( x1, y1 + 6 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, 1.f ) ), 4 );

		ImGui::GetBackgroundDrawList( )->AddLine( ImVec2( x1 - 5, y1 ), ImVec2( x1 + 5, y1 ),
		                                          ImGui::GetColorU32( *g_config.find< ImVec4 >( "visuals_recoil_crosshair_color" ) ), 2 );
		ImGui::GetBackgroundDrawList( )->AddLine( ImVec2( x1, y1 - 5 ), ImVec2( x1, y1 + 5 ),
		                                          ImGui::GetColorU32( *g_config.find< ImVec4 >( "visuals_recoil_crosshair_color" ) ), 2 );
	}

	for ( int index = 0; index < 64; index++ ) {
		if ( index == 0 )
			continue;

		auto player = sdk::game::get_entity( index );

		if ( !player )
			continue;

		if ( player->team_id( ) == local_player->team_id( ) )
			continue;

		if ( player->life_state( ) != sdk::life_alive )
			continue;

		if ( player->dormant( ) )
			continue;

		// Not doing parsing.
		//		if ( !player->spotted_by_mask( ) )
		//			continue;

		auto box = calculate_box( player );

		if ( !box.second )
			continue;

		auto draw_list = ImGui::GetBackgroundDrawList( );

		if ( *g_config.find< bool >( "visuals_boxes" ) ) {
			auto color = *g_config.find< ImVec4 >( "visuals_boxes_color" );

			draw_list->AddRect( ImVec2( box.first.x - 1, box.first.y - 1 ), ImVec2( box.first.z + 1, box.first.w + 1 ),
			                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ) );
			draw_list->AddRect( ImVec2( box.first.x + 1, box.first.y + 1 ), ImVec2( box.first.z - 1, box.first.w - 1 ),
			                    ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ) );
			draw_list->AddRect( ImVec2( box.first.x, box.first.y ), ImVec2( box.first.z, box.first.w ), ImGui::GetColorU32( color ) );
		}

		if ( *g_config.find< bool >( "visuals_names" ) ) {
			auto color = *g_config.find< ImVec4 >( "visuals_names_color" );

			ImGui::PushFont( font );

			auto text_size     = ImGui::CalcTextSize( player->player_info( ).name );
			auto text_position = ImVec2( box.first.x + ( box.first.z - box.first.x ) / 2 - ( text_size.x / 2 ), box.first.y - text_size.y - 2 );

			draw_list->AddText( ImVec2( text_position.x + 1, text_position.y + 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    player->player_info( ).name );
			draw_list->AddText( text_position, ImGui::GetColorU32( color ), player->player_info( ).name );

			ImGui::PopFont( );
		}

		if ( *g_config.find< bool >( "visuals_weapons" ) ) {
			auto color = *g_config.find< ImVec4 >( "visuals_weapons_color" );
			auto icons = *g_config.find< bool >( "visuals_weapons_icons" );

			ImGui::PushFont( icons ? font_icons : font_indicator );

			const char* item_icons[] = { "`", // 0 - default
				                         "B",    "C",    "D",    "E",    "none", "none", "F",    "G",    "H",

				                         "I", // 10
				                         "J",    "none", "K",    "L",    "none", "M",    "N",    "none", "O",

				                         "none", // 20
				                         "none", "none", "z",    "P",    "Q",    "R",    "S",    "T",    "U",

				                         "V", // 30
				                         "W",    "\\",   "Y",    "Z",    "[",    "X",    "none", "]",    "^",

				                         "_", // 40
				                         "`",    "`",    "a",    "b",    "c",    "d",    "e",    "f",    "g",

				                         "none", // 50
				                         "none", "none", "none", "none", "none", "none", "0",    "none", "k",

				                         "l", // 60
				                         "m",    "none", "n",    "o",

				                         "none", "none", "none", "none",

				                         "none", // 69
				                         "1",    "none", "2",    "none", "k",    "3",    "4",    "none", "5", "none", "none", "d", "e", "b" };

			const char* item_names[] = { "Knife", // 0 - default
				                         "Deagle",
				                         "Dual Berettas",
				                         "FiveseveN",
				                         "Glock",
				                         "none",
				                         "none",
				                         "AK-47",
				                         "AUG",
				                         "AWP",

				                         "Famas", // 10
				                         "G3SG1",
				                         "none",
				                         "Galil Ar",
				                         "M249",
				                         "none",
				                         "M4A4",
				                         "Mac-10",
				                         "none",
				                         "P90",

				                         "none", // 20
				                         "none",
				                         "none",
				                         "MP5-SD",
				                         "UMP-45",
				                         "XM1014",
				                         "Bizon",
				                         "Mag7",
				                         "Negev",
				                         "Sawed-Off",

				                         "Tec-9", // 30
				                         "Zeus",
				                         "P2000",
				                         "MP7",
				                         "MP9",
				                         "Nova",
				                         "P250",
				                         "none",
				                         "SCAR-20",
				                         "SG553",

				                         "SSG-08", // 40
				                         "Knife",
				                         "Knife",
				                         "Flash",
				                         "Nade",
				                         "Smoke",
				                         "Molotov",
				                         "Decoy",
				                         "Incendiary",
				                         "C4",

				                         "none", // 50
				                         "none",
				                         "none",
				                         "none",
				                         "none",
				                         "none",
				                         "none",
				                         "Medi-Shot",
				                         "none",
				                         "Knife",

				                         "M4A1-S", // 60
				                         "USP-S",
				                         "none",
				                         "CZ75A",
				                         "R8 Revolver",

				                         "none",
				                         "none",
				                         "none",
				                         "Tactical Grenade",

				                         "Hands", // 69
				                         "Breach Charge",
				                         "none",
				                         "Tablet",
				                         "none",
				                         "Knife",
				                         "Axe",
				                         "Hammer",
				                         "none",
				                         "Wrench",
				                         "none",
				                         "Spectral Shiv",
				                         "Fire Bomb",
				                         "Diversion Device",
				                         "Frag Grenade" };

			auto text = item_names[ player->get_weapon( )->weapon_id( ) ];
			auto icon = item_icons[ player->get_weapon( )->weapon_id( ) ];

			auto text_size     = ImGui::CalcTextSize( icons ? icon : text );
			auto text_position = ImVec2( box.first.x + ( box.first.z - box.first.x ) / 2 - ( text_size.x / 2 ), box.first.w + ( icons ? 2 : 0 ) );

			draw_list->AddText( ImVec2( text_position.x + 1, text_position.y + 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );
			draw_list->AddText( ImVec2( text_position.x - 1, text_position.y + 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );
			draw_list->AddText( ImVec2( text_position.x + 1, text_position.y - 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );
			draw_list->AddText( ImVec2( text_position.x - 1, text_position.y - 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );

			draw_list->AddText( ImVec2( text_position.x, text_position.y + 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );
			draw_list->AddText( ImVec2( text_position.x, text_position.y + 1 ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );
			draw_list->AddText( ImVec2( text_position.x + 1, text_position.y ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );
			draw_list->AddText( ImVec2( text_position.x - 1, text_position.y ), ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ),
			                    icons ? icon : text );

			draw_list->AddText( text_position, ImGui::GetColorU32( color ), icons ? icon : text );

			ImGui::PopFont( );
		}

		if ( *g_config.find< bool >( "visuals_health_bars" ) ) {
			auto color_rgb = *g_config.find< ImVec4 >( "visuals_health_bars_color" );
			ImVec4 color_hsv{ 0.f, 0.f, 0.f, color_rgb.w };

			ImGui::ColorConvertRGBtoHSV( color_rgb.x, color_rgb.y, color_rgb.z, color_hsv.x, color_hsv.y, color_hsv.z );

			auto health_percent       = -( static_cast< float >( player->health( ) ) / 100.f ) + 1.f;
			auto health_bar_position  = ImVec2( box.first.x - 2, box.first.y + ( box.first.z - box.first.x ) * health_percent );
			auto health_bar_hsv_color = ImVec4( color_hsv.x - ( 0.3f * health_percent ), color_hsv.y, color_hsv.z, color_hsv.w );

			ImVec4 color_health_rgb{ 0.f, 0.f, 0.f, color_rgb.w };

			ImGui::ColorConvertHSVtoRGB( health_bar_hsv_color.x, health_bar_hsv_color.y, health_bar_hsv_color.z, color_health_rgb.x,
			                             color_health_rgb.y, color_health_rgb.z );

			draw_list->AddRectFilled( ImVec2( health_bar_position.x - 4, box.first.y - 1 ), ImVec2( health_bar_position.x, box.first.w + 1 ),
			                          ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color_rgb.w - 0.5f ) ) );
			draw_list->AddRectFilled( ImVec2( health_bar_position.x - 3, health_bar_position.y ), ImVec2( health_bar_position.x - 1, box.first.w ),
			                          ImGui::GetColorU32( color_health_rgb ) );
		}
	}

	ImGui::GetBackgroundDrawList( )->Flags |= ImDrawListFlags_AntiAliasedLines;
}