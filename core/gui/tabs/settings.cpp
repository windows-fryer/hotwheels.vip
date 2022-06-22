#include "../gui.h"
#include "../helpers/helpers.h"
#include "../../../dependencies/imgui/cpp/imgui_stdlib.h"

void gui::tabs::settings( )
{
	static std::string current_config_name = { };

	ImGui::BeginChild( _( "settings" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "settings" ) ).x / 2 );
		ImGui::Text( _( "settings" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		gui::helpers::render_color_picker( _( "menu accent" ), &c::get<color>( vars.color_menu_accent ), true, 19, true );

		ImGui::PushItemWidth( ImGui::GetContentRegionAvail( ).x );
		ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( ImGui::GetStyle( ).FramePadding.x, 2 ) );

		gui::helpers::render_listbox( _( "##config.list" ), &gui::g_data.m_selected_config, [ ]( int index )
			{
				return c::vec_file_names.at( index ).c_str( );
			}, c::vec_file_names.size( ), 5 );

		current_config_name = !c::vec_file_names.empty( ) ? c::vec_file_names.at( gui::g_data.m_selected_config ) : _( "" );

		ImGui::InputTextWithHint( _( "##config.file" ), _( "enter file name" ), &gui::g_data.config_file );

		ImGui::PopStyleVar( );
		ImGui::PopItemWidth( );

		if ( ImGui::Button( _( "create" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
		{
			if ( !c::save( gui::g_data.config_file ) )
			{
				logging::push_console_color( FOREGROUND_RED );
				logging::print( _( "[hotwheels] - error - failed to create \"{}\" config" ), gui::g_data.config_file );
				logging::pop_console_color( );
			}

			gui::g_data.config_file.clear( );
			c::refresh( );
		}

		if ( ImGui::Button( _( "save" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 15 ) ) )
			ImGui::OpenPopup( _( "confirmation##config.save" ) );

		ImGui::SameLine( );

		if ( ImGui::Button( _( "load" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
		{
			if ( !c::load( current_config_name ) )
			{
				logging::push_console_color( FOREGROUND_RED );
				logging::print( _( "[hotwheels] - error - failed to load \"{}\" config" ), current_config_name );
				logging::pop_console_color( );
			}
		}

		if ( ImGui::Button( _( "remove" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			ImGui::OpenPopup( _( "confirmation##config.remove" ) );

		if ( ImGui::Button( _( "refresh" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			c::refresh( );

		ImGui::Checkbox( _( "menu fade" ), &c::get<bool>( vars.menu_fade ), 8 );

		/* todo - check for edge bug logs / jump bug logs and more */
		if ( c::get<bool>( vars.log_config_print ) )
			gui::helpers::render_color_picker( _( "logs prefix color" ), &c::get<color>( vars.color_log_prefix ), true, 19, true );

		ImGui::Checkbox( _( "config logs" ), &c::get<bool>( vars.log_config_print ), 8 );
		if ( c::get<bool>( vars.log_config_print ) )
			gui::helpers::render_color_picker( _( "config logs color" ), &c::get<color>( vars.color_log_config_print ), false, 19, false );

		ImGui::Checkbox( _( "discord rich presence" ), &c::get<bool>( vars.misc_discord_rpc ), 8 );

		if ( ImGui::BeginPopupModal( _( "confirmation##config.remove" ), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar ) )
		{
			ImGui::Text( ( "are you sure you want to remove \"%s\" configuration?" ), current_config_name.c_str( ) );
			ImGui::Spacing( );

			if ( ImGui::Button( _( "no" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 15 ) ) )
				ImGui::CloseCurrentPopup( );

			ImGui::SameLine( );

			if ( ImGui::Button( _( "yes" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			{
				c::remove( gui::g_data.m_selected_config );

				gui::g_data.m_selected_config = 0;

				ImGui::CloseCurrentPopup( );
			}

			ImGui::EndPopup( );
		}

		if ( ImGui::BeginPopupModal( _( "confirmation##config.save" ), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar ) )
		{
			ImGui::Text( _( "are you sure you want to save \"%s\" configuration?" ), current_config_name.c_str( ) );
			ImGui::Spacing( );

			if ( ImGui::Button( _( "no" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2, 15 ) ) )
				ImGui::CloseCurrentPopup( );

			ImGui::SameLine( );

			if ( ImGui::Button( _( "yes" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
			{
				if ( !c::save( current_config_name ) )
				{
					logging::push_console_color( FOREGROUND_RED );
					logging::print( _( "[hotwheels] - error - failed to save \"{}\" config" ), current_config_name );
					logging::pop_console_color( );
				}

				ImGui::CloseCurrentPopup( );
			}

			ImGui::EndPopup( );
		}

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild( _( "scripts" ), ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "scripts" ) ).x / 2 );
		ImGui::Text( _( "scripts" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}
}