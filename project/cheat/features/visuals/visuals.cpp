//
// Created by Liga on 6/23/2022.
//

#include "visuals.hpp"

#include "../../helpers/interfaces/interfaces.hpp"
#include "../menu/cfg/config.h"

void visuals::impl::update( )
{
	if ( not c::get< bool >( vars.esp_toggle ) )
		return;

	auto player_manager = g_interfaces.client_game_context->player_manager;

	if ( !player_manager )
		return;

	auto local_player = player_manager->local_player;

	if ( !local_player )
		return;

//	auto local_solider = local_player->GetSoldier( );
//
//	if ( !local_solider )
//		return;
//
//	[[likely]] if ( !local_solider->IsAlive( ) ) return;
//
//	for ( int index = 0; index < 70; index++ ) {
//		auto player = player_manager->players[ index ]; // Made sdk this time
//
//		if ( !player )
//			continue;
//
//		if ( player == local_player )
//			continue;
//
//		bool teammate   = player->team_id == local_player->team_id;
//		bool squad_mate = player->squad_id == local_player->squad_id;
//	}
}
