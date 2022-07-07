//
// Created by liga on 7/1/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_OVERLAY_HPP
#define HOTWHEELS_CSGO_EXTERNAL_OVERLAY_HPP

#include <d3d11.h>
#include <dxgi1_4.h>

#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/imgui/imgui_impl_dx11.h"
#include "../../../dependencies/imgui/imgui_impl_win32.h"

namespace overlay
{
	inline ID3D11Device* device{ };
	inline ID3D11DeviceContext* device_context{ };
	inline IDXGISwapChain* swap_chain{ };
	inline ID3D11RenderTargetView* render_target_view{ };

	void init( );
	void shutdown( );
} // namespace overlay

#endif // HOTWHEELS_CSGO_EXTERNAL_OVERLAY_HPP
