//
// Created by liga on 6/30/2022.
//

#ifndef HOTWHEELS_BF4_PLAYER_MANAGER_HPP
#define HOTWHEELS_BF4_PLAYER_MANAGER_HPP

#include <iostream>

#include "../../global/snakeify.hpp"
#include "client_player.hpp"

namespace sdk
{
	struct player_manager {
		PAD( 0x16 )
		virtual client_player** spectators( ) = 0;

		PAD( 0x538 )
		client_player* local_player;
		client_player* players[ 71 ];
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_PLAYER_MANAGER_HPP
