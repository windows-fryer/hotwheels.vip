//
// Created by Liga on 6/22/2022.
//

#include "present.hpp"
#include "../../../helpers/modules/modules.hpp"

bool punkbuster_check( )
{
	static auto screenshot_module = g_game.pattern_scan( "48 8B 0D ? ? ? ? 48 85 C9 74 24" ).relative( 0x3 ).as< std::uintptr_t* >( );

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
