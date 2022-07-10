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
	constexpr std::uint32_t user_info             = 0x52C0;
	constexpr std::uint32_t entity_index          = 0x64;
	constexpr std::uint32_t player_health         = 0x100;
	constexpr std::uint32_t competitive_rank      = 0x1A84;
	constexpr std::uint32_t player_resource       = 0x320A190;
	constexpr std::uint32_t account               = 0x117B8; // money
	constexpr std::uint32_t my_weapons            = 0x2E08;
	constexpr std::uint32_t weapon_id             = 0x2FBA; // item definition index
	constexpr std::uint32_t item_id               = 0x2FD0;
	constexpr std::uint32_t fallback_paint_kit    = 0x31D8;
	constexpr std::uint32_t fallback_seed         = 0x31DC;
	constexpr std::uint32_t fallback_wear         = 0x31E0;
	constexpr std::uint32_t fallback_stat_trak    = 0x31E4;
	constexpr std::uint32_t delta_ticks           = 0x174;
	constexpr std::uint32_t account_id            = 0x2FD8;
	constexpr std::uint32_t quality               = 0x2FBC;
	constexpr std::uint32_t active_weapon         = 0x2F08;
	constexpr std::uint32_t weapon_info           = 0x33F0; // 8B 81 ? ? ? ? 85 C0 0F 84 ? ? ? ? C3 pastor
} // namespace offsets

#endif // HOTWHEELS_CSGO_EXTERNAL_OFFSETS_HPP
