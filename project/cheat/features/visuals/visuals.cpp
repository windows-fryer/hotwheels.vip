//
// Created by liga on 7/5/2022.
//

#include "visuals.hpp"

#include "../../cheat.hpp"

#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"

#include "../../helpers/math/math.hpp"
#include "../../sdk/enums/flags.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/matrix.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../../sdk/structs/vector.hpp"

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

	return { { left, top, right, bottom }, true };
}

void visuals::routine( )
{
	ImGui::GetBackgroundDrawList( )->Flags &= ~ImDrawListFlags_AntiAliasedLines;

	auto local_player = sdk::game::local_player( );

	if ( !local_player )
		return;

	sdk::vector punch_angle = local_player->aim_punch_angle( );

	if ( *g_config.find< bool >( "visuals_recoil_crosshair" ) && !punch_angle.is_zero( ) ) {
		int x1 = 1920 / 2;
		int y1 = 1080 / 2;

		int x2 = 1920 / local_player->default_fov( );
		int y2 = 1080 / local_player->default_fov( );

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

		auto player = sdk::game::get_player( index );

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

		auto local_box = calculate_box( player );

		if ( !local_box.second )
			continue;

		if ( *g_config.find< bool >( "visuals_boxes" ) ) {
			auto color = *g_config.find< ImVec4 >( "visuals_boxes_color" );

			ImGui::GetBackgroundDrawList( )->AddRect( ImVec2( local_box.first.x - 1, local_box.first.y - 1 ),
			                                          ImVec2( local_box.first.z + 1, local_box.first.w + 1 ),
			                                          ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ) );
			ImGui::GetBackgroundDrawList( )->AddRect( ImVec2( local_box.first.x + 1, local_box.first.y + 1 ),
			                                          ImVec2( local_box.first.z - 1, local_box.first.w - 1 ),
			                                          ImGui::GetColorU32( ImVec4( 0.f, 0.f, 0.f, color.w - 0.5f ) ) );
			ImGui::GetBackgroundDrawList( )->AddRect( ImVec2( local_box.first.x, local_box.first.y ), ImVec2( local_box.first.z, local_box.first.w ),
			                                          ImGui::GetColorU32( color ) );
		}

		
	}

	ImGui::GetBackgroundDrawList( )->Flags |= ImDrawListFlags_AntiAliasedLines;
}