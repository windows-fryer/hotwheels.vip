#include "../gui.h"
#include "../../cfg/config.h"
#include "../helpers/helpers.h"

void gui::tabs::visuals( )
{
	ImGui::BeginChild("esp", ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f,"esp" ).x / 2 );
		ImGui::Text("esp" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::Checkbox("spectators list", &c::get<bool>( vars.esp_spectators_list ) );
		if ( c::get<bool>( vars.esp_spectators_list ) )
		{
			gui::helpers::render_color_picker("spectators list spectating local", &c::get<color>( vars.color_esp_spectators_list_spectating_local ), true, 17, false );
			ImGui::SameLine( );
			gui::helpers::render_color_picker("spectators list spectating other", &c::get<color>( vars.color_esp_spectators_list_spectating_other ), true, 36, false );
		}

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild("chams", ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f,"chams" ).x / 2 );
		ImGui::Text("chams" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		gui::helpers::render_combo("chams type", &gui::g_data.m_selected_cham,"players\0arms\0weapons", -7 );

		switch ( gui::g_data.m_selected_cham )
		{
		case 0:
		{
			ImGui::Checkbox("enable##players", &c::get<bool>( vars.chams_visible ) );
			if ( c::get<bool>( vars.chams_visible ) )
				gui::helpers::render_color_picker("chams color##players", &c::get<color>( vars.chams_visible_color ), true, 19, false );

			ImGui::Checkbox("xqz##players", &c::get<bool>( vars.chams_invisible ) );
			if ( c::get<bool>( vars.chams_invisible ) )
				gui::helpers::render_color_picker("chams color##players xqz", &c::get<color>( vars.chams_invisible_color ), true, 19, false );

			if ( c::get<bool>( vars.chams_visible ) || c::get<bool>( vars.chams_invisible ) || c::get<bool>( vars.chams_visible_overlay ) || c::get<bool>( vars.chams_invisible_overlay ) )
			{
				gui::helpers::render_combo("material##players", &c::get<int>( vars.chams_material ),"flat\0textured\0\0", -7 );
				ImGui::Checkbox("wireframe##players", &c::get<bool>( vars.chams_wireframe ) );
			}

			ImGui::Checkbox("render original##players", &c::get<bool>( vars.chams_render_original ) );

			ImGui::Checkbox("enable overlay##players", &c::get<bool>( vars.chams_visible_overlay ) );
			if ( c::get<bool>( vars.chams_visible_overlay ) )
				gui::helpers::render_color_picker("chams visible overlay color##players", &c::get<color>( vars.chams_visible_overlay_color ), true, 19, false );

			ImGui::Checkbox("xqz overlay##players", &c::get<bool>( vars.chams_invisible_overlay ) );
			if ( c::get<bool>( vars.chams_invisible_overlay ) )
				gui::helpers::render_color_picker("chams xqz overlay color##players", &c::get<color>( vars.chams_invisible_overlay_color ), true, 19, false );

			if ( c::get<bool>( vars.chams_visible_overlay ) || c::get<bool>( vars.chams_invisible_overlay ) )
				gui::helpers::render_combo("overlay material##players", &c::get<int>( vars.chams_overlay_material ),"glow\0snow\0\0", -7 );
			break;
		}
		case 1:
		{
			ImGui::Checkbox("enable##arms", &c::get<bool>( vars.chams_arm ) );
			if ( c::get<bool>( vars.chams_arm ) )
			{
				gui::helpers::render_color_picker("chams color##arms", &c::get<color>( vars.chams_arm_color ), true, 19, false );
				gui::helpers::render_combo("material##arms", &c::get<int>( vars.chams_arm_material ),"flat\0textured\0\0", -7 );
			}

			if ( c::get<bool>( vars.chams_arm ) || c::get<bool>( vars.chams_arm_overlay ) )
			{
				ImGui::Checkbox("wireframe##arms", &c::get<bool>( vars.chams_arm_wireframe ) );
				ImGui::Checkbox("render original##arms", &c::get<bool>( vars.chams_arm_render_original ) );
			}

			ImGui::Checkbox("enable overlay##arms", &c::get<bool>( vars.chams_arm_overlay ) );
			if ( c::get<bool>( vars.chams_arm_overlay ) )
			{
				gui::helpers::render_color_picker("chams overlay color##arms", &c::get<color>( vars.chams_arm_overlay_color ), true, 19, false );
				gui::helpers::render_combo("overlay material##arms", &c::get<int>( vars.chams_overlay_arm_material ),"glow\0snow\0\0", -7 );
			}
			break;
		}
		case 2:
		{
			ImGui::Checkbox("enable##weapons", &c::get<bool>( vars.chams_weapon ) );
			if ( c::get<bool>( vars.chams_weapon ) )
			{
				gui::helpers::render_color_picker("chams color##weapon", &c::get<color>( vars.chams_weapon_color ), true, 19, false );

				gui::helpers::render_combo("material##weapons", &c::get<int>( vars.chams_weapon_material ),"flat\0textured\0\0", -7 );
			}

			if ( c::get<bool>( vars.chams_weapon ) || c::get<bool>( vars.chams_weapon_overlay ) )
			{
				ImGui::Checkbox("wireframe##weapons", &c::get<bool>( vars.chams_weapon_wireframe ) );
				ImGui::Checkbox("render original##weapons", &c::get<bool>( vars.chams_weapon_render_original ) );
			}

			ImGui::Checkbox("enable overlay##weapons", &c::get<bool>( vars.chams_weapon_overlay ) );
			if ( c::get<bool>( vars.chams_weapon_overlay ) )
			{
				gui::helpers::render_color_picker("chams overlay color##weapons", &c::get<color>( vars.chams_weapon_overlay_color ), true, 19, false );
				gui::helpers::render_combo("overlay material##weapons", &c::get<int>( vars.chams_overlay_weapon_material ),"glow\0snow\0\0", -7 );
			}
			break;
		}
		}

		ImGui::EndChild( );
	}

	ImGui::BeginChild("glow", ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f,"glow" ).x / 2 );
		ImGui::Text("glow" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild("world", ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f,"world" ).x / 2 );
		ImGui::Text("world" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}
}