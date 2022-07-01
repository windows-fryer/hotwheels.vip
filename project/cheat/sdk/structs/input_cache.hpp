//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_INPUT_CACHE_HPP
#define HOTWHEELS_BF4_INPUT_CACHE_HPP

#include <iostream>

#include "../../global/snakeify.hpp"

namespace sdk
{
	struct input_cache {
		PAD( 0x4 )

		float event[ 0xFD ];
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_INPUT_CACHE_HPP
