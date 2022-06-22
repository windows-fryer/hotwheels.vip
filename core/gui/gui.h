#pragma once
#include "../../common.h"

namespace gui
{
	void init( IDirect3DDevice9* device );
	void revert( );
	void render( );

	struct gui_data_t
	{
		bool m_initialised = false;
		bool m_opened = true;
		int m_tab = 0;
		int m_selected_cham = 0;
		int m_selected_color = 0;
		int m_selected_config = 0;
		std::string config_file = {};
	} inline g_data;

	namespace input
	{
		bool init( );
		void revert( );

		inline HWND window = nullptr;
		inline WNDPROC old_wnd_proc = nullptr;
	}

	namespace tabs
	{
		void aimbot( );
		void visuals( );
		void misc( );
		void movement( );
		void skins( );
		void settings( );
		void fonts( );
	}
}

namespace fonts
{
	inline ImFont* verdana;
	inline ImFont* verdanab;
}