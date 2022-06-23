//
// Created by Liga on 6/22/2022.
//

#include "bitblt.hpp"
#include "../present/present.hpp"

bool hooks::bitblt::bitblt_detour( HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop )
{
	screenshot_running = true;

	while ( !ran_present ) {
		Sleep( 1 );
	}

	bool result = bitblt_hook.call_original( hdc, x, y, cx, cy, hdc_src, x1, y1, rop );

	ran_present        = false;
	screenshot_running = false;

	return result;
}
