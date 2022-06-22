//
// Created by Liga on 6/22/2022.
//

#ifndef HOTWHEELS_BF4_PRESENT_HPP
#define HOTWHEELS_BF4_PRESENT_HPP

#include <d3d11.h>

#include "../../../dependencies/sdk/sdk.h"
#include "../../../features/menu/gui/gui.h"
#include "../../hooks.hpp"

namespace hooks
{
	CREATE_HOOK_HELPER( present_hook, long( IDXGISwapChain* self, UINT sync_interval, UINT flags ), long );

	struct present {
		static long present_detour( IDXGISwapChain* self, UINT sync_interval, UINT flags );

		static void init( )
		{
			gui::init( DxRenderer::GetInstance( )->m_pDevice, DxRenderer::GetInstance( )->m_pContext );

			present_hook.create( ( *reinterpret_cast< void*** >( DxRenderer::GetInstance( )->m_pScreen->m_pSwapChain ) )[ 8 ], present_detour,
			                     "present_detour" );
		}

		static void shutdown( )
		{
			present_hook.disable( );
		}
	};
} // namespace hooks

#endif // HOTWHEELS_BF4_PRESENT_HPP
