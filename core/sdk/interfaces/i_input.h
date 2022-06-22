#pragma once
#include "../datatypes/c_usercmd.h"

#define MULTIPLAYER_BACKUP 150

class i_input
{
public:
	std::byte			pad0[ 0xC ];			
	bool				m_track_ir_available;	
	bool				m_mouse_initialized;	
	bool				m_mouse_active;			
	std::byte			pad1[ 0x9A ];			
	bool				m_camera_in_third_person;
	std::byte			pad2[ 0x2 ];			
	math::vec3				m_camera_offset;	
	std::byte			pad3[ 0x38 ];			
	c_usercmd* m_commands;				
	c_verified_user_cmd* m_verified_commands;	

	[[nodiscard]] c_usercmd* get_user_cmd( const int nSequenceNumber ) const
	{
		return &m_commands[ nSequenceNumber % MULTIPLAYER_BACKUP ];
	}

	[[nodiscard]] c_verified_user_cmd*  get_verified_cmd( const int sequence_number ) const
	{
		return &m_verified_commands[ sequence_number % MULTIPLAYER_BACKUP ];
	}
};

static_assert( sizeof( i_input ) == 0xF8 );