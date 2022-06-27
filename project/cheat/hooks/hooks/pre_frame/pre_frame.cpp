//
// Created by Liga on 6/22/2022.
//

#include "pre_frame.hpp"
#include "../../../features/misc/misc.hpp"

void hooks::pre_frame::pre_frame_detour( float delta )
{
	reinterpret_cast< pre_frame_update_t >( original_pre_frame_update )( delta );

	g_misc.update( );
}