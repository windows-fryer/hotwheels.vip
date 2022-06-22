#pragma once
#include "../../../utilities/memory/memory.h"
using c_base_handle = std::uintptr_t;

class i_client_entity_list
{
public:
	template <typename T>
	T* get_entity_from_index( int index )
	{
		return mem::call_vfunc<T*>( this, 3, index );
	}

	template <typename T>
	T* get_entity_from_handle( int index )
	{
		return mem::call_vfunc<T*>( this, 4, index );
	}

	int get_highest_entity_index( ) 
	{
		return mem::call_vfunc<int>( this, 6 );
	}
};