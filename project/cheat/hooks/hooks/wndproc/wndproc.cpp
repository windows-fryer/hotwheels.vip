//
// Created by Liga on 6/22/2022.
//

#include "wndproc.hpp"
#include "../../../features/menu/gui/gui.h"

long hooks::wndproc::wndproc_detour( HWND window, unsigned int message, WPARAM parameter, LPARAM long_parameter )
{
	if ( message == WM_KEYDOWN && parameter == VK_INSERT )
		gui::g_data.m_opened = !gui::g_data.m_opened;

	if ( gui::g_data.m_initialised && gui::g_data.m_opened && ImGui_ImplWin32_WndProcHandler( window, message, parameter, long_parameter ) )
		return 1L;

	return call_window_proc( hooks::wndproc_hook, window, message, parameter, long_parameter );
}
