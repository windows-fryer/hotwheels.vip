//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_SCREEN_HPP
#define HOTWHEELS_BF4_SCREEN_HPP

#include <d3d11.h>
#include <iostream>

#include "../../global/snakeify.hpp"

namespace sdk
{
	struct screen {
		PAD( 0x58 );

		std::uint32_t width;
		std::uint32_t height;
		std::uint32_t window_width;
		std::uint32_t window_height;

		PAD( 0x88 );

		IDXGISwapChain* swap_chain;
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_SCREEN_HPP
