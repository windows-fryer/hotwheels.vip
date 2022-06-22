#pragma once
#include "../../../utilities/memory/memory.h"
class c_material;

class i_model_render
{
public:
	void force_override_material( c_material* mat )
	{
		return mem::call_vfunc<void>( this, 1, mat, 0, 0 );
	}

	bool is_forced_material_override( )
	{
		return mem::call_vfunc<bool>( this, 2 );
	}
};