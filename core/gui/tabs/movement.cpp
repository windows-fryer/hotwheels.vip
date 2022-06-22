#include "../gui.h"

void gui::tabs::movement( )
{
	ImGui::BeginChild( _( "movement" ), ImVec2( ImGui::GetContentRegionAvail( ).x / 2 - 10, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "movement" ) ).x / 2 );
		ImGui::Text( _( "movement" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::SameLine( );

	ImGui::BeginChild( _( "indicators" ), ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y / 2 - 10 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "indicators" ) ).x / 2 );
		ImGui::Text( _( "indicators" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}

	ImGui::BeginChild( _( "recorder" ), ImVec2( ImGui::GetContentRegionAvail( ).x, ImGui::GetContentRegionAvail( ).y - 25 ), true );
	{
		ImGui::PushFont( fonts::verdanab );

		ImGui::SetCursorPosX( ImGui::GetContentRegionAvail( ).x / 2 - fonts::verdanab->CalcTextSizeA( fonts::verdanab->FontSize, FLT_MAX, 0.0f, _( "recorder" ) ).x / 2 );
		ImGui::Text( _( "recorder" ) );

		ImGui::PopFont( );

		ImGui::Spacing( );

		ImGui::EndChild( );
	}
}