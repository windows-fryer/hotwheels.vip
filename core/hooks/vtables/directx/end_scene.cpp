#include <intrin.h>
#include "../../hooks.h"
#include "../../../gui/gui.h"
#include "../../../sdk/interfaces/interfaces.h"
#include "../../../hacks/visuals/players/esp/esp.h"

LONG __stdcall h::end_scene( IDirect3DDevice9* device )
{
	static auto original = detours::end_scene.get_original<decltype( &h::end_scene )>( );
	static void* static_return_address = nullptr;

	SEH_START

		if ( static_return_address == nullptr )
		{
			MEMORY_BASIC_INFORMATION memory_basic_information;
			VirtualQuery( _ReturnAddress( ), &memory_basic_information, sizeof( MEMORY_BASIC_INFORMATION ) );

			char module_name[ MAX_PATH ];
			GetModuleFileName( static_cast< HMODULE >( memory_basic_information.AllocationBase ), module_name, MAX_PATH );

			if ( strstr( module_name, _("gameoverlayrenderer.dll" ) ) != nullptr )
				static_return_address = _ReturnAddress( );
		}

	if ( _ReturnAddress( ) == static_return_address )
	{
		if ( !gui::g_data.m_initialised )
			gui::init( device );

		ImGui_ImplDX9_NewFrame( );
		ImGui_ImplWin32_NewFrame( );
		ImGui::NewFrame( );

		gui::render( );

		esp::spectators_list( );

		ImGui::EndFrame( );
		ImGui::Render( );
		ImGui_ImplDX9_RenderDrawData( ImGui::GetDrawData( ) );
	}

	SEH_END

		return original( device );
}