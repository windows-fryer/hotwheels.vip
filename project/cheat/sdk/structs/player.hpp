//
// Created by liga on 7/3/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_PLAYER_HPP
#define HOTWHEELS_CSGO_EXTERNAL_PLAYER_HPP

#include "collideable.hpp"
#include "matrix.hpp"
#include "player_info.hpp"
#include "vector.hpp"
#include "weapon.hpp"
#include "weapon_info.hpp"

#include "../enums/life_state.hpp"

namespace sdk
{
	struct player {
		int flags( );
		int default_fov( );
		int team_id( );
		int index( );
		int health( );
		int money( );

		bool dormant( );
		bool spotted_by_mask( );

		sdk::weapon* get_weapon( );
		sdk::weapon* get_weapon( int index );
		sdk::weapon_info get_weapon_info( );

		std::string_view competitive_rank( );

		life_state life_state( );

		sdk::player_info player_info( );

		sdk::collideable* collideable( );

		sdk::matrix_3x4 rgfl( );

		sdk::vector aim_punch_angle( );
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_PLAYER_HPP
