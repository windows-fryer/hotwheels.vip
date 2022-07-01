//
// Created by Liga on 6/22/2022.
//

#ifndef HOTWHEELS_BF4_PRESENT_HPP
#define HOTWHEELS_BF4_PRESENT_HPP

#include <d3d11.h>

#include "../../../features/menu/gui/gui.h"
#include "../../../helpers/interfaces/interfaces.hpp"
#include "../../../helpers/vfunc/vfunc.hpp"
#include "../../../sdk/include.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( present_hook, long( IDXGISwapChain* self, UINT sync_interval, UINT flags ), long );

	inline bool screenshot_running = false;
	inline bool punkbuster_running = false;

	inline bool ran_present = false;

	struct present {
		static long present_detour( IDXGISwapChain* self, UINT sync_interval, UINT flags );

		static void init( )
		{
			gui::init( g_interfaces.directx_renderer->device, g_interfaces.directx_renderer->context );

			present_hook.create( g_vfunc.get_virtual_function_index( g_interfaces.directx_renderer->screen->swap_chain, 0x8 ), present_detour,
			                     "present_detour" );
		}

		static void shutdown( )
		{
			present_hook.disable( );
		}
	};
} // namespace hooks

#endif // HOTWHEELS_BF4_PRESENT_HPP
