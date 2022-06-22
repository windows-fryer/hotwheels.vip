#include "../gui.h"


void gui::tabs::aimbot( )
{
	ImGui::BeginChild( _( "weapon selection" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "weapon selection" ) ).x / 2 );
		ImGui::Text( _( "weapon selection" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::BeginChild( _( "triggerbot" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "triggerbot" ) ).x / 2 );
		ImGui::Text( _( "triggerbot" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::SetCursorPosY( 31 );

	ImGui::BeginChild( _( "weapon settings" ), ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "weapon settings" ) ).x / 2 );
		ImGui::Text( _( "weapon settings" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}
}