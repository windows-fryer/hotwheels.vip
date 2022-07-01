//
// Created by Liga on 6/23/2022.
//

#include "misc.hpp"
#include "../menu/cfg/config.h"

void unlock_all( )
{
	// iirc this is a flag saying you're a b1g dice developer.

	*reinterpret_cast< std::uint8_t* >( *reinterpret_cast< std::uintptr_t* >( 0x1423717C0 ) + 0x54 ) = c::get< bool >( vars.misc_unlock_all );
}

void fly( )
{
	// Everything here is pasted and garbage
}

void misc::impl::update( )
{
	unlock_all( );
	fly( );
}
