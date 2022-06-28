//
// Created by Liga on 6/23/2022.
//

#include "visuals.hpp"
#include "../../../dependencies/sdk/sdk.h"
#include "../menu/cfg/config.h"

void visuals::impl::update( )
{
	if ( not c::get< bool >( vars.esp_toggle ) )
		return;

	auto game_context = ClientGameContext::GetInstance( );

	[[unlikely]] if ( !game_context ) return; // This should be in every sense impossible.

	auto player_manager = game_context->m_pPlayerManager;

	if ( !player_manager )
		return;

	auto local_player = player_manager->m_pLocalPlayer;

	if ( !local_player )
		return;

	auto local_solider = local_player->GetSoldier( );

	if ( !local_solider )
		return;

	[[likely]] if ( !local_solider->IsAlive( ) ) return;

	for ( int index = 0; index < MAX_PLAYERS; index++ ) {
		auto player = player_manager->m_ppPlayers[ index ]; // Nice hungarian notation sdk developers. m_pp??

		if ( !player )
			continue;

		if ( player == local_player )
			continue;

		bool teammate   = player->m_TeamId == local_player->m_TeamId;
		bool squad_mate = player->m_SquadId1 == local_player->m_SquadId1;
	}
}
