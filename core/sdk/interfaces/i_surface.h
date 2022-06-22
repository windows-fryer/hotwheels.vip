#pragma once
#include "../../../utilities/memory/memory.h"

class i_surface
{
public:
	void unlock_cursor( )
	{
		return mem::call_vfunc<void>( this, 66 );
	}

	void set_text_color( int r, int g, int b, int a )
	{
		return mem::call_vfunc<void>( this, 25, r, g, b, a );
	}
};