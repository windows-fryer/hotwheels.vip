#include <cstring>
#include <discord_register.h>
#include <discord_rpc.h>
#include <mutex>

#include "rpc.h"

#include "../../sdk/interfaces/interfaces.h"
#include "../../cfg/config.h"

static float last_presence_update = 0.0f;
static bool is_initialized = false;

void discord_rpc::update( ) {
	if ( is_initialized && !c::get<bool>( vars.misc_discord_rpc ) )
	{
		Discord_ClearPresence( );
		Discord_Shutdown( );

		is_initialized = false;
		last_presence_update = 0.0f;
	}
	else if ( !is_initialized && c::get<bool>( vars.misc_discord_rpc ) )
	{
		DiscordEventHandlers handlers;

		memset( &handlers, 0, sizeof( handlers ) );

		Discord_Initialize( _( "982918430141341696" ), &handlers, true, nullptr );

		is_initialized = true;
		last_presence_update = 0.0f;
	}

	if ( !is_initialized || i::globals->m_real_time - last_presence_update < 15.0f )
		return;

	last_presence_update = i::globals->m_real_time;

	DiscordRichPresence presence;

	memset( &presence, 0, sizeof( presence ) );

	presence.details = _( "Counter-Strike: Global Offensive | beta" );

	if ( !i::engine_client->in_game( ) )
		presence.state = _( "in menu" );
	else
	{
		char presence_status_buffer[ 64 ];

		memset( presence_status_buffer, 0, sizeof( presence_status_buffer ) );
		sprintf_s( presence_status_buffer, _( "playing on: %s" ), i::engine_client->get_level_name_short( ) );

		presence.state = presence_status_buffer;
	}

	presence.instance = 1;

	Discord_UpdatePresence( &presence );
}