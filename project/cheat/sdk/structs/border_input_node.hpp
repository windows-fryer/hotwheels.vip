//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_BORDER_INPUT_NODE_HPP
#define HOTWHEELS_BF4_BORDER_INPUT_NODE_HPP

#include <iostream>

#include "../../global/snakeify.hpp"
#include "input_cache.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"

namespace sdk
{
	struct border_input_node {
		PAD( 0x8 )

		input_cache* input_cache;
		PAD( 0x30 )

		std::int64_t vtable;
		PAD( 0x8 )

		keyboard* keyboard;
		mouse* mouse;
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_BORDER_INPUT_NODE_HPP
