//
// Created by Liga on 6/22/2022.
//

#include "present.hpp"

long hooks::present::present_detour( IDXGISwapChain* self, UINT sync_interval, UINT flags )
{
	ImGui_ImplDX11_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );

	gui::render( );

	ImGui::EndFrame( );
	ImGui::Render( );
	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );

	return present_hook.call_original( self, sync_interval, flags );
}
