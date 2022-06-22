#include "../../hooks.h"
#include "../../../gui/gui.h"

long __stdcall h::reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters )
{
	static auto original = detours::reset.get_original<decltype( &reset )>( );

	if ( !gui::g_data.m_initialised )
		return original( device, presentation_parameters );

	ImGui_ImplDX9_InvalidateDeviceObjects( );

	const HRESULT hReset = original( device, presentation_parameters );

	if ( hReset == D3D_OK )
		ImGui_ImplDX9_CreateDeviceObjects( );

	return hReset;
}