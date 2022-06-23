//
// Created by Liga on 6/22/2022.
//

#include "hooks.hpp"
#include "hooks/bitblt/bitblt.hpp"
#include "hooks/present/present.hpp"
#include "hooks/wndproc/wndproc.hpp"

void hooks::impl::init( )
{
	MH_Initialize( );

	hooks::wndproc::init( );
	hooks::present::init( );
	hooks::bitblt::init( );

	MH_EnableHook( MH_ALL_HOOKS );
}

void hooks::impl::shutdown( )
{
	hooks::wndproc::shutdown( );

	MH_RemoveHook( MH_ALL_HOOKS );
	MH_Uninitialize( );
}
