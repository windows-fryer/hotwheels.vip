//
// Created by Liga on 6/22/2022.
//

#include "pre_frame.hpp"

void hooks::pre_frame::pre_frame_detour( float delta )
{
	//	auto player_manager = ClientGameContext::GetInstance( )->m_pPlayerManager;
	//
	//	if ( player_manager ) {
	//		auto local_player = player_manager->m_pLocalPlayer;
	//
	//		if ( local_player ) {
	//			auto local_soldier = local_player->GetSoldier( );
	//
	//			if ( local_soldier ) {
	//				local_soldier->m_pWeaponComponent->GetActiveSoldierWeapon( )->m_pPrimary->m_RecoilAngleX = 0;
	//				local_soldier->m_pWeaponComponent->GetActiveSoldierWeapon( )->m_pPrimary->m_RecoilAngleY = 0;
	//				local_soldier->m_pWeaponComponent->GetActiveSoldierWeapon( )->m_pPrimary->m_RecoilAngleZ = 0;
	//			}
	//		}
	//	}

	return reinterpret_cast< pre_frame_update_t >( original_pre_frame_update )( delta );
}