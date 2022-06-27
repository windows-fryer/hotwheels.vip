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

		ImGui::Checkbox( "unlock all", &c::get< bool >( vars.misc_unlock_all ) );

		if ( ImGui::IsItemHovered( ) ) {
			ImGui::SetTooltip( "Guns do not work. Anything developer related is a sure way to be banned." );
		}

		ImGui::EndChild( );
	}
}