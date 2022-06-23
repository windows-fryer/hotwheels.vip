#include "../gui.h"

void gui::tabs::movement( )
{
	ImGui::BeginChild( "movement", ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "movement" ).x / 2 );
		ImGui::Text( "movement" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild( "indicators", ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "indicators" ).x / 2 );
		ImGui::Text( "indicators" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::BeginChild( "recorder", ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 -
		                      fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, "recorder" ).x / 2 );
		ImGui::Text( "recorder" );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}
}