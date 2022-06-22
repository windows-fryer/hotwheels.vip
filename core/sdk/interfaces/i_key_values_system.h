#pragma once

class i_key_values_system
{
public:
	virtual void register_sizeof_key_values( int size ) = 0;
	virtual void* alloc_key_values_memory( int size ) = 0;
	virtual void free_key_values_memory( void* memory ) = 0;
};

using key_values_system_fn = i_key_values_system * ( __cdecl* )( );
