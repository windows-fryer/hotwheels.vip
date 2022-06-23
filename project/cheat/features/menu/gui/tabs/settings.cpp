#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/cpp/imgui_stdlib.h"
#include "../gui.h"
#include "../helpers/helpers.h"

void gui::tabs::settings( )
{
	static std::string current_config_name = { };

	ImGui::BeginChild( "settings", ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "settings" ).x / 2 );
		ImGui::Text( "settings" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		gui::helpers::render_color_picker( "menu accent", &c::get< color >( vars.color_menu_accent ), true, 19, true );

		ImGui::PushItemWidth( ImGui::GetContentRegionAvail( ).x );
		ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( ImGui::GetStyle( ).FramePadding.x, 2 ) );

		gui::helpers::render_listbox(
			"##config.list", &gui::g_data.m_selected_config, []( int index ) { return c::vec_file_names.at( index ).c_str( ); },
			c::vec_file_names.size( ), 5 );

		current_config_name = !c::vec_file_names.empty( ) ? c::vec_file_names.at( gui::g_data.m_selected_config ) : "";

//		ImGui::InputTextWithHint( "##config.file", "enter file name", &gui::g_data.config_file );

		ImGui::PopStyleVar( );
		ImGui::PopItemWidth( );

		if ( ImGui::Button( "create", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) ) {
			if ( !c::save( gui::g_data.config_file ) ) {
			}

			gui::g_data.config_file.clear( );
			c::refresh( );
		}

		if ( ImGui::Button( "save", ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 15 ) ) )
			ImGui::OpenPopup( "confirmation##config.save" );

		ImGui::SameLine( );

		if ( ImGui::Button( "load", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) ) {
			if ( !c::load( current_config_name ) ) {
			}
		}

		if ( ImGui::Button( "remove", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			ImGui::OpenPopup( "confirmation##config.remove" );

		if ( ImGui::Button( "refresh", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			c::refresh( );

		ImGui::Checkbox( "menu fade", &c::get< bool >( vars.menu_fade ), 8 );

		/* todo - check for edge bug logs / jump bug logs and more */
		if ( c::get< bool >( vars.log_config_print ) )
			gui::helpers::render_color_picker( "logs prefix color", &c::get< color >( vars.color_log_prefix ), true, 19, true );

		ImGui::Checkbox( "config logs", &c::get< bool >( vars.log_config_print ), 8 );
		if ( c::get< bool >( vars.log_config_print ) )
			gui::helpers::render_color_picker( "config logs color", &c::get< color >( vars.color_log_config_print ), false, 19, false );

		ImGui::Checkbox( "discord rich presence", &c::get< bool >( vars.misc_discord_rpc ), 8 );

		if ( ImGui::BeginPopupModal( "confirmation##config.remove", nullptr,
		                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar ) ) {
			ImGui::Text( "are you sure you want to remove \"%s\" configuration?", current_config_name.c_str( ) );
			ImGui::Spacing( );

			if ( ImGui::Button("no", ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 15 ) ) )
				ImGui::CloseCurrentPopup( );

			ImGui::SameLine( );

			if ( ImGui::Button("yes", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			{
				c::remove( gui::g_data.m_selected_config );

				gui::g_data.m_selected_config = 0;

				ImGui::CloseCurrentPopup( );
			}

			ImGui::EndPopup( );
		}

		if ( ImGui::BeginPopupModal( "confirmation##config.save", nullptr,
		                             ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar ) ) {
			ImGui::Text( "are you sure you want to save \"%s\" configuration?", current_config_name.c_str( ) );
			ImGui::Spacing( );

			if ( ImGui::Button( "no", ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 15 ) ) )
				ImGui::CloseCurrentPopup( );

			ImGui::SameLine( );

			if ( ImGui::Button( "yes", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) ) {
				if ( !c::save( current_config_name ) ) {
				}

				ImGui::CloseCurrentPopup( );
			}

			ImGui::EndPopup( );
		}

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild( "scripts", ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "scripts" ).x / 2 );
		ImGui::Text( "scripts" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}
}