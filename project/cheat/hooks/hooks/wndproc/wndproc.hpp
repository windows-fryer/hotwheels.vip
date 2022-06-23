#ifndef WEDNESDAY_WTF_WNDPROC_HPP
#define WEDNESDAY_WTF_WNDPROC_HPP

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
		}

		static void shutdown( )
		{
			set_window_long( find_window( nullptr, "Battlefield 4" ), GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( wndproc_hook ) );
		}
	};
} // namespace hooks

#endif // WEDNESDAY_WTF_WNDPROC_HPP
