#include "../../hooks.h"
#include "../../../gui/gui.h"
#include "../../../sdk/interfaces/interfaces.h"

void __fastcall h::lock_cursor( i_surface* thisptr, int edx )
{
	static auto original = detours::lock_cursor.get_original<decltype( &lock_cursor )>( );

	if ( gui::g_data.m_opened )
	{
		i::surface->unlock_cursor( );
		return;
	}

	original( thisptr, edx );
}
