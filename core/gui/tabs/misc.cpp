#include "../gui.h"
#include "../../cfg/config.h"
#include "../helpers/helpers.h"

static int key = 0, keystyle = 0;

void gui::tabs::misc( )
{
	ImGui::BeginChild( _( "game" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "game" ) ).x / 2 );
		ImGui::Text( _( "game" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::Checkbox( _( "custom netgraph" ), &c::get<bool>( vars.custom_netgraph ) ); 
		if ( c::get<bool>( vars.custom_netgraph ) )
		{
			gui::helpers::render_color_picker( _( "netgraph color" ), &c::get<color>( vars.color_custom_netgraph ), true, 17, false );

			if ( ImGui::Button( _( "restore color##netgraph" ), ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
				c::get<color>( vars.color_custom_netgraph ) = color( 229, 229, 178, 255 );
		}

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild( _( "exploits" ), ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "exploits" ) ).x / 2 );
		ImGui::Text( _( "exploits" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::Checkbox( _( "sv_pure bypass" ), &c::get<bool>( vars.sv_pure_bypass ) );

		ImGui::EndChild( );
	}
}