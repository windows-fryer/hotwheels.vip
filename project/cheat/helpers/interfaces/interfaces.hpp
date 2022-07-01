//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_INTERFACES_HPP
#define HOTWHEELS_BF4_INTERFACES_HPP

#include "../../sdk/include.hpp"

namespace interfaces
{
	struct impl {
		sdk::directx_renderer* directx_renderer;
		sdk::border_input_node* border_input_node;
		sdk::client_game_context* client_game_context;

		void init( );
		void shutdown( );
	};
} // namespace interfaces

inline interfaces::impl g_interfaces;

#endif // HOTWHEELS_BF4_INTERFACES_HPP
