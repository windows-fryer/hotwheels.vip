#include "../../hooks.h"
#include "../../../gui/gui.h"
#include "../../../sdk/interfaces/interfaces.h"

long  __stdcall h::wnd_proc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam )
{
	if ( message == WM_KEYDOWN && wparam == VK_INSERT )
		gui::g_data.m_opened = !gui::g_data.m_opened;

	i::input_system->enable_input( !gui::g_data.m_opened );

	if ( gui::g_data.m_initialised && gui::g_data.m_opened && ImGui_ImplWin32_WndProcHandler( hwnd, message, wparam, lparam ) )
		return 1L;

	return CallWindowProcW( gui::input::old_wnd_proc, hwnd, message, wparam, lparam );
}