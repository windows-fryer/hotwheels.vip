//
// Created by Liga on 6/22/2022.
//

#include "vfunc.hpp"

uintptr_t* virtual_func::impl::get_virtual_table( void* instance )
{
	return *( uintptr_t** )instance;
}

uintptr_t* virtual_func::impl::get_virtual_function_index( void* instance, const std::uint32_t index )
{
	return ( uintptr_t* )get_virtual_table( instance )[ index ];
}