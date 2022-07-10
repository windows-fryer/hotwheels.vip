//
// Created by liga on 7/9/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_WEAPON_HPP
#define HOTWHEELS_CSGO_EXTERNAL_WEAPON_HPP

#include "weapon_info.hpp"

namespace sdk
{
	struct weapon {
		void set_item_id( int id );
		void set_fallback_paint_kit( int kit );
		void set_fallback_seed( int seed );
		void set_fallback_wear( float wear );
		void set_fallback_stat_trak( int stat_trak );
		void set_quality( int quality );

		short weapon_id( );

		weapon_info weapon_info( );
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_WEAPON_HPP
