//
// Created by Liga on 6/22/2022.
//

#ifndef HOTWHEELS_BF4_BITBLT_HPP
#define HOTWHEELS_BF4_BITBLT_HPP

#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( bitblt_hook, bool( __stdcall )( HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop ), bool );

	struct bitblt {
		static bool __stdcall bitblt_detour( HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop );

		static void init( )
		{
			bitblt_hook.create( &BitBlt, bitblt_detour, "bitblt_detour" );
		}

		static void shutdown( )
		{
			bitblt_hook.disable( );
		}
	};
} // namespace hooks

#endif // HOTWHEELS_BF4_BITBLT_HPP
