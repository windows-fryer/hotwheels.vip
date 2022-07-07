//
// Created by liga on 7/3/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP
#define HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP

#include <iostream>

namespace offsets
{
	constexpr std::uint32_t local_player          = 0xDBF4CC;
	constexpr std::uint32_t player_flags          = 0x104;
	constexpr std::uint32_t next_attack           = 0x2D80;
	constexpr std::uint32_t force_jump            = 0x52858A8;
	constexpr std::uint32_t client_state          = 0x58CFDC;
	constexpr std::uint32_t view_angles           = 0x4D90;
	constexpr std::uint32_t aim_punch_angle       = 0x303C;
	constexpr std::uint32_t default_fov           = 0x333C;
	constexpr std::uint32_t collision             = 0x320; // i_collideable
	constexpr std::uint32_t rgfl                  = 0x444;
	constexpr std::uint32_t view_matrix           = 0x4DCD244;
	constexpr std::uint32_t last_outgoing_command = 0x4D2C;
	constexpr std::uint32_t entity_list           = 0x4DDB92C;
	constexpr std::uint32_t team_id               = 0xF4;
	constexpr std::uint32_t life_state            = 0x25F;
	constexpr std::uint32_t dormant               = 0xED;
	constexpr std::uint32_t spotted_by_mask       = 0x980;
} // namespace offsets

#endif // HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP
