#pragma once
#include <Windows.h>
#include <chrono>
#include <iostream>

#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/imgui_internal.h"

#include "../../../dependencies/imgui/dx11/imgui_impl_dx11.h"
#include "../../../dependencies/imgui/win32/imgui_impl_win32.h"

#include "../../../dependencies/imgui/imgui_freetype.h"

#include "../../../global/snakeify.hpp"
#include "../other/color.hpp"

namespace gui
{
	void init( ID3D11Device* device, ID3D11DeviceContext* context );
	void revert( );
	void render( );

	struct gui_data_t {
		bool m_initialised      = false;
		bool m_opened           = true;
		int m_tab               = 0;
		int m_selected_cham     = 0;
		int m_selected_color    = 0;
		int m_selected_config   = 0;
		std::string config_file = { };
	} inline g_data;

	namespace tabs
	{
		void aimbot( );
		void visuals( );
		void misc( );
		void movement( );
		void skins( );
		void settings( );
		void fonts( );
	} // namespace tabs
} // namespace gui

namespace fonts
{
	inline ImFont* verdana;
	inline ImFont* verdanab;
} // namespace fonts