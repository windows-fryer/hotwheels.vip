#pragma once
#include "../../../utilities/memory/memory.h"
#include "../../sdk/datatypes/key_values.h"
#include "../../sdk/classes/c_material.h"

class i_material_system
{
public:
	c_material* find_material( const char* name, const char* group_name = nullptr, bool complain = true, const char* complain_prefix = nullptr )
	{
		return mem::call_vfunc<c_material*>( this, 84, name, group_name, complain, complain_prefix );
	}

	c_material* create_material( const char* name, c_key_values* key_values )
	{
		return mem::call_vfunc<c_material*>( this, 83, name, key_values );
	}
};