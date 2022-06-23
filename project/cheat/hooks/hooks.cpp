//
// Created by Liga on 6/22/2022.
//

#include "hooks.hpp"
#include "hooks/bitblt/bitblt.hpp"
#include "hooks/pre_frame/pre_frame.hpp"
#include "hooks/present/present.hpp"
#include "hooks/wndproc/wndproc.hpp"

void hooks::impl::init( )
{
	MH_Initialize( );

	hooks::wndproc::init( );
	hooks::bitblt::init( );
	hooks::present::init( );

	MH_EnableHook( MH_ALL_HOOKS );

	hooks::pre_frame::init( );
}

void hooks::impl::shutdown( )
{
	hooks::wndproc::shutdown( );

	MH_RemoveHook( MH_ALL_HOOKS );
	MH_Uninitialize( );

	hooks::pre_frame::shutdown( );
}
