//
// Created by liga on 7/9/2022.
//

#include "changer.hpp"

#include "../../helpers/configs/config.hpp"
#include "../../helpers/driver/driver.hpp"

#include "../../helpers/math/math.hpp"
#include "../../sdk/enums/quality.hpp"
#include "../../sdk/structs/game.hpp"
#include "../../sdk/structs/offsets.hpp"

void changer::routine( )
{
// Removes the point of an external.
//	while ( true ) {
//		auto local_player = sdk::game::local_player( );
//
//		if ( !local_player )
//			continue;
//
//		for ( auto index = 0; index < 8; index++ ) {
//			auto current_weapon = local_player->get_weapon( index );
//
//			if ( !current_weapon )
//				continue;
//
//			auto weapon_id = current_weapon->weapon_id( );
//
//			if ( weapon_id != 0x7 )
//				continue;
//
//			current_weapon->set_item_id( -1 );
//
//			current_weapon->set_fallback_paint_kit( 639 );
//			current_weapon->set_fallback_wear( 0.00001f );
//		}
//
//		Sleep( 1 );
//	}
}