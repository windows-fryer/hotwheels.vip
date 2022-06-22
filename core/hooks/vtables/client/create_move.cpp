#include "../../hooks.h"
#include "../../../../utilities/logging.h"
#include "../../../sdk/datatypes/c_usercmd.h"
#include "../../../sdk/interfaces/interfaces.h"

static void __stdcall create_move( int sequence_number, float input_sample_frametime, bool is_active, bool& send_packet )
{
	static auto original = detours::create_move_proxy.get_original<decltype( &h::create_move_proxy )>( );

	original( i::client, 0, sequence_number, input_sample_frametime, is_active );

	c_usercmd* cmd = i::input->get_user_cmd( sequence_number );
	c_verified_user_cmd* verified_cmd = i::input->get_verified_cmd( sequence_number );

	if ( cmd == nullptr || verified_cmd == nullptr || !is_active )
		return;

	SEH_START

	cmd->m_view_angles.normalize( );
	cmd->m_view_angles.clamp( );

	// globals::send_packet = send_packet;

	SEH_END

		verified_cmd->cmd = *cmd;
	verified_cmd->hash_crc = cmd->get_checksum( );
}

__declspec( naked ) void __fastcall h::create_move_proxy( [[maybe_unused]] i_base_client_dll* thisptr, [[maybe_unused]] int edx, [[maybe_unused]] int sequence_number, [[maybe_unused]] float input_sample_frametime, [[maybe_unused]] bool is_active )
{
	__asm
	{
		push	ebp
		mov		ebp, esp;
		push	ebx;
		push	esp;
		push	dword ptr[ is_active ];
		push	dword ptr[ input_sample_frametime ];
		push	dword ptr[ sequence_number ];
		call	create_move
			pop		ebx
			pop		ebp
			retn	0Ch
	}
}
