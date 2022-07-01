//
// Created by liga on 6/30/2022.
//

#ifndef HOTWHEELS_BF4_ONLINE_ID_HPP
#define HOTWHEELS_BF4_ONLINE_ID_HPP

#include <iostream>

#include "../../global/snakeify.hpp"

namespace sdk
{
	struct online_id {
		std::uint64_t persona_id;
		char id[ 0x11 ];
		PAD( 0x7 )
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_ONLINE_ID_HPP
