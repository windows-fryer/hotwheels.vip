//
// Created by liga on 7/9/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_WEAPON_INFO_HPP
#define HOTWHEELS_CSGO_EXTERNAL_WEAPON_INFO_HPP

#include <iostream>

namespace sdk
{
	struct weapon_info {
	private:
		char pad[ 0x14 ];

	public:
		int max_clip1;
		int max_clip2;
		int default_clip1;
		int default_clip2;
		int primary_max_reserve_ammo;
		int secondary_max_reserve_ammo;
		const char* world_model;
		const char* view_model;
		const char* dropped_model;

	private:
		char pad_2[ 0x50 ];

	public:
		std::uint32_t hud_name;
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_WEAPON_INFO_HPP
