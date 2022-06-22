#include "../../hooks.h"
#include "../../../sdk/classes/entity.h"
#include "../../../../utilities/logging.h"
#include "../../../hacks/discord-rpc/rpc.h"
#include "../../../sdk/interfaces/interfaces.h"

void __fastcall h::frame_stage_notify( i_base_client_dll* thisptr, int edx, e_client_frame_stage stage )
{
	static auto original = detours::frame_stage_notify.get_original<decltype( &frame_stage_notify )>( );

	SEH_START

		discord_rpc::update( );

		if ( !i::engine_client->in_game( ) )
			return original( thisptr, edx, stage );

	c_base_entity* local = i::client_entity_list->get_entity_from_index<c_base_entity>( i::engine_client->get_local_player_index( ) );

	if ( !local )
		return original( thisptr, edx, stage );

	SEH_END

		original( thisptr, edx, stage );
}