#pragma once
#include <cstdint>

#include "../../../utilities/math/vector.h"
#include "../../../utilities/helpers/bit_flag.h"
#include "../../../utilities/encryption/crc32.h"

enum e_command_buttons : int
{
	in_attack = ( 1 << 0 ),
	in_jump = ( 1 << 1 ),
	in_duck = ( 1 << 2 ),
	in_forward = ( 1 << 3 ),
	in_back = ( 1 << 4 ),
	in_use = ( 1 << 5 ),
	in_cancel = ( 1 << 6 ),
	in_left = ( 1 << 7 ),
	in_right = ( 1 << 8 ),
	in_moveleft = ( 1 << 9 ),
	in_moveright = ( 1 << 10 ),
	in_second_attack = ( 1 << 11 ),
	in_run = ( 1 << 12 ),
	in_reload = ( 1 << 13 ),
	in_left_alt = ( 1 << 14 ),
	in_right_alt = ( 1 << 15 ),
	in_score = ( 1 << 16 ),
	in_speed = ( 1 << 17 ),
	in_walk = ( 1 << 18 ),
	in_zoom = ( 1 << 19 ),
	in_first_weapon = ( 1 << 20 ),
	in_second_weapon = ( 1 << 21 ),
	in_bullrush = ( 1 << 22 ),
	in_first_grenade = ( 1 << 23 ),
	in_second_grenade = ( 1 << 24 ),
	in_middle_attack = ( 1 << 25 ),
	in_use_or_reload = ( 1 << 26 )
};

#pragma pack(push, 4)
class c_usercmd
{
public:
	virtual ~c_usercmd( ) { }		
	int m_command_number;		
	int m_tick_count;			
	math::vec3 m_view_angles;		
	math::vec3 m_aim_direction;	
	float m_forwardmove;		
	float m_sidemove;			
	float m_upmove;			
	bit_flag_t<int> m_buttons;
	std::uint8_t m_impulse;			
	int m_weapon_select;	
	int m_weapon_sub_type;	
	int m_random_seed;		
	short m_mouse_delta_x;	
	short m_mouse_delta_y;	
	bool m_has_been_predicted;
	math::vec3 m_head_angles;	
	math::vec3 m_head_offset;	

	[[nodiscard]] crc32_t get_checksum( ) const
	{
		crc32_t hash_crc = 0UL;

		crc32::init( &hash_crc );
		crc32::process_buffer( &hash_crc, &m_command_number, sizeof( m_command_number ) );
		crc32::process_buffer( &hash_crc, &m_tick_count, sizeof( m_tick_count ) );
		crc32::process_buffer( &hash_crc, &m_view_angles, sizeof( m_view_angles ) );
		crc32::process_buffer( &hash_crc, &m_aim_direction, sizeof( m_aim_direction ) );
		crc32::process_buffer( &hash_crc, &m_forwardmove, sizeof( m_forwardmove ) );
		crc32::process_buffer( &hash_crc, &m_sidemove, sizeof( m_sidemove ) );
		crc32::process_buffer( &hash_crc, &m_upmove, sizeof( m_upmove ) );
		crc32::process_buffer( &hash_crc, &m_buttons, sizeof( m_buttons ) );
		crc32::process_buffer( &hash_crc, &m_impulse, sizeof( m_impulse ) );
		crc32::process_buffer( &hash_crc, &m_weapon_select, sizeof( m_weapon_select ) );
		crc32::process_buffer( &hash_crc, &m_weapon_sub_type, sizeof( m_weapon_sub_type ) );
		crc32::process_buffer( &hash_crc, &m_random_seed, sizeof( m_random_seed ) );
		crc32::process_buffer( &hash_crc, &m_mouse_delta_x, sizeof( m_mouse_delta_x ) );
		crc32::process_buffer( &hash_crc, &m_mouse_delta_y, sizeof( m_mouse_delta_y ) );
		crc32::end( &hash_crc );

		return hash_crc;
	}
};
static_assert( sizeof( c_usercmd ) == 0x64 );

class c_verified_user_cmd
{
public:
	c_usercmd	cmd;	// 0x00
	crc32_t		hash_crc;	// 0x64
};
static_assert( sizeof( c_verified_user_cmd ) == 0x68 );
#pragma pack(pop)