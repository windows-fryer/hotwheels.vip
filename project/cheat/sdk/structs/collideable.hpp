//
// Created by liga on 7/5/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_COLLIDEABLE_HPP
#define HOTWHEELS_CSGO_EXTERNAL_COLLIDEABLE_HPP

#include "vector.hpp"

namespace sdk
{
	struct collideable {
		sdk::vector mins( );
		sdk::vector maxs( );
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_COLLIDEABLE_HPP
