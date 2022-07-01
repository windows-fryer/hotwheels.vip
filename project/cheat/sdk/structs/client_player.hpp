//
// Created by liga on 6/30/2022.
//

#ifndef HOTWHEELS_BF4_CLIENT_PLAYER_HPP
#define HOTWHEELS_BF4_CLIENT_PLAYER_HPP

#include <iostream>

#include "../../global/snakeify.hpp"
#include "online_id.hpp"
#include "weak_pointer.hpp"

namespace sdk
{
	struct client_player {
		VIRTUAL_PAD( )
		VIRTUAL_PAD( )
		VIRTUAL_PAD( )
		VIRTUAL_PAD( )
		virtual bool is_in_vehicle( ) = 0;
		PAD( 0x10 )

		char* name;
		PAD( 0x18 )

		online_id online_id;
		PAD( 0x138 )

		std::int32_t squad_id;
		PAD( 0x7B4 )

		void* selected_customization_asset; // Use later for unlock all battle pickups
		PAD( 0x8 )

		std::int64_t selected_active_unlocks;
		PAD( 0xA68 )

		bool is_ai_player;
		bool is_spectator;

		PAD( 0x2 )
		std::uint32_t team_id;

		PAD( 0xD8 )

	};
} // namespace sdk

#endif // HOTWHEELS_BF4_CLIENT_PLAYER_HPP
