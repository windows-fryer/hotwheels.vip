#ifndef HOTWHEELS_BF4_WNDPROC_HPP
#define HOTWHEELS_BF4_WNDPROC_HPP

#include <Windows.h>

#include "../../../global/snakeify.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	inline WNDPROC wndproc_hook;

	struct wndproc {
		static long win_api wndproc_detour( HWND window, unsigned int message, WPARAM parameter, LPARAM long_parameter );

		static void init( )
		{
			wndproc_hook = reinterpret_cast< WNDPROC >(
				set_window_long( find_window( nullptr, "Battlefield 4" ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_detour ) ) );

			console::log( "[HOOKS] " );

			console::log< fmt::color::cyan >( "Created hook [ {} ]\n", "wndproc_detour" );
		}

		static void shutdown( )
		{
			set_window_long( find_window( nullptr, "Battlefield 4" ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_hook ) );
		}
	};
} // namespace hooks

#endif // HOTWHEELS_BF4_WNDPROC_HPP
