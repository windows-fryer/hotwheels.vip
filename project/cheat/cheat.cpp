//
// Created by Liga on 6/21/2022.
//

#include "cheat.hpp"

#include "hooks/hooks.hpp"

void cheat::impl::init( )
{
	g_hooks.init( );
}

void cheat::impl::shutdown( )
{
	g_hooks.shutdown( );
}
