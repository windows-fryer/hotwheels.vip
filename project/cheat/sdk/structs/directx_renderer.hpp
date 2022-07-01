//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_DIRECTX_RENDERER_HPP
#define HOTWHEELS_BF4_DIRECTX_RENDERER_HPP

#include <d3d11.h>
#include <iostream>

#include "../../global/snakeify.hpp"
#include "screen.hpp"

namespace sdk
{
	struct directx_renderer {
		PAD( 0x38 );

		screen* screen;
		PAD( 0xC0 );

		ID3D11Device* device;
		ID3D11DeviceContext* context;
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_DIRECTX_RENDERER_HPP
