//
// Created by liga on 7/3/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_GAME_HPP
#define HOTWHEELS_CSGO_EXTERNAL_GAME_HPP

#include "player.hpp"

namespace sdk
{
	struct game {
		static player* local_player( );

		static player* get_player( int index );
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_GAME_HPP
