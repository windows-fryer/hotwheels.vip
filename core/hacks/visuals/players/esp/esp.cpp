#include <vector>

#include "../../../../cfg/config.h"
#include "../../../../sdk/classes/entity.h"
#include "../../../../sdk/interfaces/interfaces.h"
#include "../../../../gui/gui.h"
#include "esp.h"

void esp::spectators_list( )
{
	if ( !c::get<bool>( vars.esp_spectators_list ) )
		return;

	if ( !i::engine_client->in_game( ) )
		return;

	c_base_entity* local = i::client_entity_list->get_entity_from_index<c_base_entity>( i::engine_client->get_local_player_index( ) );
	if ( local == nullptr )
		return;

	std::vector<std::pair<std::string, color>> spectators;
	static ImVec2 tab_window_pos = { };
	static ImVec2 window_size = { };

	for ( int i = 0; i <= i::globals->m_max_clients; i++ )
	{
		c_base_entity* entity = i::client_entity_list->get_entity_from_index<c_base_entity>( i );
		if ( !entity || entity->is_alive( ) || entity->dormant( ) )
			continue;

		c_base_entity* spectated_player = i::client_entity_list->get_entity_from_handle<c_base_entity>( entity->observer_target( ) );
		if ( !spectated_player || !spectated_player->is_alive( ) )
			continue;

		player_info_t spectating_info = {}, spectated_info = {};
		i::engine_client->get_player_info( entity->index( ), &spectating_info );
		i::engine_client->get_player_info( spectated_player->index( ), &spectated_info );

		char spectate_buffer[ 1024 ];
		sprintf_s( spectate_buffer, _( "%s -> %s" ), spectating_info.m_name, spectated_info.m_name );

		if ( strstr( spectate_buffer, _( "GOTV" ) ) )
			continue;

		spectators.push_back( std::pair<std::string, color>( spectate_buffer, spectated_player == local ? c::get<color>( vars.color_esp_spectators_list_spectating_local ) : c::get<color>( vars.color_esp_spectators_list_spectating_other ) ) );
	}

	if ( !spectators.empty( ) )
	{
		ImGui::GetStyle( ).Alpha = 1.0f;
		ImGui::SetNextWindowSize( ImVec2( window_size.x, fonts::verdanab->CalcTextSizeA( 11.f, FLT_MAX, 0.0f, _( "spectators" ) ).y + 10 ) );
		ImGui::Begin( _( "hw-spectators-header-window" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse );
		{
			tab_window_pos = ImGui::GetWindowPos( );

			ImGui::PushFont( fonts::verdanab );
			ImGui::SetCursorPos( ImVec2( ImGui::GetWindowSize( ).x / 2 - fonts::verdanab->CalcTextSizeA( 11.f, FLT_MAX, 0.0f, _( "spectators" ) ).x / 2, 25 / 2 - 8 ) );
			ImGui::TextColored( c::get<color>( vars.color_menu_accent ).get_imvec4( ), _( "spectators" ) );
			ImGui::PopFont( );
		}
		ImGui::End( );

		ImGui::SetNextWindowPos( ImVec2( tab_window_pos.x, tab_window_pos.y + 25 ) );
		ImGui::Begin( _( "hw-spectators-window" ), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse );
		window_size = ImGui::GetWindowSize( );

		ImGui::PushFont( fonts::verdana );

		for ( auto spectator : spectators )
			ImGui::TextColored( spectator.second.get_imvec4( ), spectator.first.c_str( ) );

		ImGui::PopFont( );

		ImGui::End( );
	}
}