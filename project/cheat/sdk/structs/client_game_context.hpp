//
// Created by liga on 6/30/2022.
//

#ifndef HOTWHEELS_BF4_CLIENT_GAME_CONTEXT_HPP
#define HOTWHEELS_BF4_CLIENT_GAME_CONTEXT_HPP

#include <iostream>

#include "../../global/snakeify.hpp"
#include "player_manager.hpp"

namespace sdk
{
	struct client_game_context {
		PAD( 0x60 );

		player_manager* player_manager;

		// m_pOnline
		// m_pGameView
		// m_pInterpolationManager
		// Yada yada
	};
} // namespace sdk

#endif // HOTWHEELS_BF4_CLIENT_GAME_CONTEXT_HPP
