//
// Created by Liga on 6/22/2022.
//

#include "present.hpp"

bool punkbuster_check( )
{
	static auto screenshot_module = reinterpret_cast< std::uintptr_t* >( OFFSET_SSMODULE );

	if ( !IsValidPtr( screenshot_module ) )
		return true;

	bool status               = *reinterpret_cast< int* >( *screenshot_module + 0x14 ) != -1;
	hooks::punkbuster_running = status;

	return status;
}

long hooks::present::present_detour( IDXGISwapChain* self, UINT sync_interval, UINT flags )
{
	if ( !screenshot_running && !punkbuster_check( ) ) {
		ImGui_ImplDX11_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );

		gui::render( );

		ImGui::EndFrame( );
		ImGui::Render( );
		ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );
	} else {
		ran_present = true;
	}

	return present_hook.call_original( self, sync_interval, flags );
}
