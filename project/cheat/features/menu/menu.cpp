//
// Created by liga on 7/7/2022.
//

#include "menu.hpp"

#include <Windows.h>
#include <filesystem>
#include <iostream>

#include <ShlObj.h>

#include "../../../dependencies/imgui/imgui.h"
#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"

void menu::routine( float ease_animation )
{
#ifdef _DEBUG
	ImGui::ShowDemoWindow( );
#endif

	float current_position{ };

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( "Aimbot", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( "RCS", g_config.find< bool >( "aimbot_rcs" ) );

		if ( *g_config.find< bool >( "aimbot_rcs" ) ) {
			ImGui::PushItemWidth( -1 );
			ImGui::SliderFloat( "##RCS X", g_config.find< float >( "aimbot_rcs_x" ), 0, 150.f, "X: %0.1f%" );
			ImGui::SliderFloat( "##RCS Y", g_config.find< float >( "aimbot_rcs_y" ), 0, 150.f, "Y: %0.1f%" );
			ImGui::SliderFloat( "##RCS SMOOTH", g_config.find< float >( "aimbot_rcs_smooth" ), 0, 2.f, "Smooth: %0.1f%" );

			ImGui::PopItemWidth( );

			ImGui::Checkbox( "RCS Error", g_config.find< bool >( "aimbot_rcs_error" ) );
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( "Visuals", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( "Boxes", g_config.find< bool >( "visuals_boxes" ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( "##Boxes Color", reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_boxes_color" ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( "Names", g_config.find< bool >( "visuals_names" ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( "##Names Color", reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_names_color" ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( "Weapons", g_config.find< bool >( "visuals_weapons" ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( "##Weapons Color", reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_weapons_color" ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( "Weapon Icons", g_config.find< bool >( "visuals_weapons_icons" ) );

		ImGui::Checkbox( "Health Bars", g_config.find< bool >( "visuals_health_bars" ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( "##Health Bars Color", reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_health_bars_color" ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::Checkbox( "Recoil Crosshair", g_config.find< bool >( "visuals_recoil_crosshair" ) );
		ImGui::SameLine( );

		ImGui::ColorEdit4( "##Recoil Crosshair Color", reinterpret_cast< float* >( g_config.find< ImVec4 >( "visuals_recoil_crosshair_color" ) ),
		                   ImGuiColorEditFlags_NoInputs );

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( "Movement", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( "Bunny Hop", g_config.find< bool >( "movement_bunny_hop" ) );

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( "Misc", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Checkbox( "Smooth Open", g_config.find< bool >( "menu_open_smooth" ) );
		if ( ImGui::Button( "Force Full Update" ) ) {
			static auto engine_dll = driver::base_address( "engine.dll" );

			auto client_state = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::client_state ) );

			driver::write< int >( reinterpret_cast< PVOID >( client_state + offsets::delta_ticks ), -1 );
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 175, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( "Configs", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		static CHAR my_documents[ MAX_PATH ]{ };
		static HRESULT result = SHGetFolderPath( nullptr, CSIDL_PERSONAL, nullptr, SHGFP_TYPE_CURRENT, my_documents );

		if ( result == S_OK ) {
			static std::string config_name{ };

			if ( ImGui::BeginListBox( "##Configs", ImVec2( 158, 75 ) ) ) {
				if ( ImGui::BeginPopupContextWindow( "##Configs Context" ) ) {
					static char config_name[ 64 ]{ };

					ImGui::PushItemWidth( 150 );
					ImGui::InputText( "##Configs Name", config_name, 64 );
					ImGui::PopItemWidth( );

					if ( ImGui::Button( "Create", ImVec2( 150, 0 ) ) ) {
						std::string config_path{ my_documents };
						config_path += "\\hotwheels\\";
						config_path += config_name;
						config_path += ".vip";

						if ( !std::filesystem::exists( config_path ) ) {
							g_config.save( config_path );

							ImGui::CloseCurrentPopup( );
						}
					}

					ImGui::EndPopup( );
				}

				std::string config_path{ my_documents };

				config_path += "\\hotwheels\\";

				std::filesystem::directory_iterator end{ };

				for ( std::filesystem::directory_iterator it{ config_path }; it != end; ++it ) {
					if ( std::filesystem::is_regular_file( it->status( ) ) ) {
						std::string file_name{ it->path( ).filename( ).string( ) };

						bool selected = config_name == file_name;

						if ( ImGui::Selectable( file_name.c_str( ), selected ) ) {
							config_name = file_name;
						}

						if ( ImGui::BeginPopupContextItem( ( std::string( "##Configs Popup " ) + file_name ).c_str( ) ) ) {
							if ( ImGui::Button( ( std::string( "Delete " ) + file_name ).c_str( ) ) ) {
								std::filesystem::remove( it->path( ) );
								ImGui::CloseCurrentPopup( );
							}

							ImGui::EndPopup( );
						}
					}
				}

				ImGui::EndListBox( );
			}

			if ( ImGui::Button( "Save", ImVec2( ImGui::GetWindowSize( ).x * 0.43f, 0 ) ) ) {
				g_config.save( std::string( my_documents ) + "/hotwheels/" + config_name );
			}
			ImGui::SameLine( );
			if ( ImGui::Button( "Load", ImVec2( ImGui::GetWindowSize( ).x * 0.43f, 0 ) ) ) {
				g_config.load( std::string( my_documents ) + "/hotwheels/" + config_name );
			}
		}

		ImGui::End( );
	}

	ImGui::SetNextWindowSize( ImVec2( 500, 0 ) );
	ImGui::SetNextWindowPos( ImVec2( 10.f + ( 5.f + 175.f ) * current_position++ * ease_animation, 10 ) );
	if ( ImGui::Begin( "Players", nullptr, ImGuiWindowFlags_AlwaysAutoResize ) ) {
		ImGui::Columns( 3, "Players", true );
		ImGui::Separator( );

		ImGui::Text( "Name" );
		ImGui::NextColumn( );

		ImGui::Text( "Rank" );
		ImGui::NextColumn( );

		ImGui::Text( "Money" );
		ImGui::NextColumn( );
		ImGui::Separator( );

		for ( int index = 0; index < 64; index++ ) {
			auto player = sdk::game::get_entity( index );

			if ( !player )
				continue;

			auto player_info = player->player_info( );

			ImGui::Text( "%s", player_info.name );
			ImGui::NextColumn( );
			ImGui::Text( "%s", player->competitive_rank( ).data( ) );
			ImGui::NextColumn( );
			ImGui::Text( "$%d", player->money( ) );
			ImGui::NextColumn( );

			ImGui::Separator( );
		}

		ImGui::Columns( 1 );
		ImGui::End( );
	}
}