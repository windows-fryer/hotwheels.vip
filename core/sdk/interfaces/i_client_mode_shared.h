#pragma once
#include "../../../utilities/math/vector.h"
#include "i_base_client_dll.h"

class c_hud_chat
{
public:
	template <typename... Args>
	void print( int chat_filter, const char* fmt, Args... args )
	{
		( *reinterpret_cast< void( __cdecl*** )( void*, int, const char*, ... ) >( this ) )[ 26 ]( this, chat_filter, fmt, args... );
	}
};

class i_client_mode_shared
{
public:
	auto m_chat_element( )
	{
		return *reinterpret_cast< c_hud_chat** >( reinterpret_cast< std::uintptr_t >( this ) + 28 );
	}
};

class i_app_system
{
private:
	virtual void function0( ) = 0;
	virtual void function1( ) = 0;
	virtual void function2( ) = 0;
	virtual void function3( ) = 0;
	virtual void function4( ) = 0;
	virtual void function5( ) = 0;
	virtual void function6( ) = 0;
	virtual void function7( ) = 0;
	virtual void function8( ) = 0;
};

class c_event_info
{
public:
	short m_class_id;
	float m_fire_delay;
	const void* m_send_table;
	const c_base_client* m_client_class;
	void* m_data;
	std::intptr_t m_packed_bits;
	int m_flags;
	std::byte pad0[ 0x16 ];
};

class i_net_channel;
class i_client_state
{
public:
	std::byte		pad0[ 0x9C ];
	i_net_channel* m_net_channel;
	int				m_challenge_nr;
	std::byte		pad1[ 0x64 ];
	int				m_signon_tate;
	std::byte		pad2[ 0x8 ];
	float			m_next_cmd_time;
	int				m_server_count;
	int				m_current_sequence;
	std::byte		pad3[ 0x54 ];
	int				m_delta_tick;
	bool			m_paused;
	std::byte		pad4[ 0x7 ];
	int				m_view_entity;
	int				m_player_slot;
	char			m_level_name[ 260 ];
	char			m_level_name_short[ 80 ];
	char			m_map_group_name[ 80 ];
	char			m_last_level_name_short[ 80 ];
	std::byte		pad5[ 0xC ];
	int				m_max_clients;
	std::byte		pad6[ 0x498C ];
	float			m_last_server_tick_time;
	bool			m_in_simulation;
	std::byte		pad7[ 0x3 ];
	int				m_old_tick_count;
	float			m_tick_remainder;
	float			m_frame_time;
	int				m_last_outgoing_command;
	int				m_chokedC_commands;
	int				m_last_command_ack;
	int				m_command_ack;
	int				m_sound_sequence;
	std::byte		pad8[ 0x50 ];
	math::vec3			m_viewangles;
	std::byte		pad9[ 0xD0 ];
	c_event_info* m_events;
};