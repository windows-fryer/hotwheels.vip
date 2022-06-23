#include "../../cfg/config.h"
#include "../gui.h"
#include "../helpers/helpers.h"

static int key = 0, keystyle = 0;

void gui::tabs::misc( )
{
	ImGui::BeginChild( "game", ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "game" ).x / 2 );
		ImGui::Text( "game" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::Checkbox( "custom netgraph", &c::get< bool >( vars.custom_netgraph ) );
		if ( c::get< bool >( vars.custom_netgraph ) ) {
			gui::helpers::render_color_picker( "netgraph color", &c::get< color >( vars.color_custom_netgraph ), true, 17, false );

			if ( ImGui::Button( "restore color##netgraph", ImVec2( ImGui::GetContentRegionAvail( ).x, 15 ) ) )
				c::get< color >( vars.color_custom_netgraph ) = color( 229, 229, 178, 255 );
		}

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild( "exploits", ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "exploits" ).x / 2 );
		ImGui::Text( "exploits" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::Checkbox( "sv_pure bypass", &c::get< bool >( vars.sv_pure_bypass ) );

		ImGui::EndChild( );
	}
}