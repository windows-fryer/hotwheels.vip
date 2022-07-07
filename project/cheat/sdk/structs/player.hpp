//
// Created by liga on 7/3/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_PLAYER_HPP
#define HOTWHEELS_CSGO_EXTERNAL_PLAYER_HPP

#include "../structs/collideable.hpp"
#include "../structs/matrix.hpp"
#include "../structs/vector.hpp"

#include "../enums/life_state.hpp"

namespace sdk
{
	struct player {
		int flags( );
		int default_fov( );
		int team_id( );

		bool dormant( );
		bool spotted_by_mask( );

		life_state life_state( );

		sdk::collideable* collideable( );

		sdk::matrix_3x4 rgfl( );

		sdk::vector aim_punch_angle( );
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_PLAYER_HPP
