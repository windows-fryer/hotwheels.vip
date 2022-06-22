#pragma once
#include "../../../utilities/encryption/crc32.h"

enum e_client_frame_stage : int
{
	frame_undefined = -1,
	frame_start,
	frame_net_update_start,
	frame_net_update_postdataupdate_start,
	frame_net_update_postdataupdate_end,
	frame_net_update_end,
	frame_render_start,
	frame_render_end,
	frame_net_full_frame_update_on_remove
};

struct player_info_t
{
	std::uint64_t m_version = 0ULL;
	union
	{
		std::uint64_t m_xuid;
		struct
		{
			std::uint32_t m_xuid_low;
			std::uint32_t m_xuid_high;
		};
	};

	char			m_name[ 128 ];
	int				m_user_id;
	char			m_steam_id[ 33 ];
	std::uint32_t	m_friends_id;
	char			m_friends_name[ 128 ];
	bool			m_fake_player;
	bool			m_is_hltv;
	crc32_t			m_custom_files[ 4 ];
	std::uint8_t	m_files_downloaded;
};

class i_engine_client
{
public:
	int get_local_player_index( )
	{
		return mem::call_vfunc<int>( this, 12 );
	}

	bool get_player_info( int index, player_info_t* info )
	{
		return mem::call_vfunc<bool>( this, 8, index, info );
	}

	bool in_game( )
	{
		return mem::call_vfunc<bool>( this, 26 );
	}

	bool is_taking_screenshot( )
	{
		return  mem::call_vfunc<bool>( this, 92 );
	}

	const char* get_level_name_short( )
	{
		return mem::call_vfunc<const char*>( this, 53 );
	}
};