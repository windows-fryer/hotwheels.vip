//
// Created by liga on 7/9/2022.
//

#include "../structs/weapon.hpp"
#include "../structs/game.hpp"
#include "../structs/offsets.hpp"

#include "../../helpers/driver/driver.hpp"

short sdk::weapon::weapon_id( )
{
	return driver::read< short >( this + offsets::weapon_id );
}

void sdk::weapon::set_item_id( int id )
{
	driver::write< int >( this + offsets::item_id, id );
}

void sdk::weapon::set_fallback_paint_kit( int kit )
{
	driver::write< int >( this + offsets::fallback_paint_kit, kit );
}

void sdk::weapon::set_fallback_seed( int seed )
{
	driver::write< int >( this + offsets::fallback_seed, seed );
}

void sdk::weapon::set_fallback_wear( float wear )
{
	driver::write< float >( this + offsets::fallback_wear, wear );
}

void sdk::weapon::set_fallback_stat_trak( int stat_trak )
{
	auto player_info = game::local_player( )->player_info( );

	driver::write< int >( this + offsets::account_id, player_info.xuidlow );
	driver::write< int >( this + offsets::fallback_stat_trak, stat_trak );
}

void sdk::weapon::set_quality( int quality )
{
	driver::write< int >( this + offsets::quality, quality );
}

sdk::weapon_info sdk::weapon::weapon_info( )
{
	return driver::read< sdk::weapon_info >( this + offsets::weapon_info );
}
