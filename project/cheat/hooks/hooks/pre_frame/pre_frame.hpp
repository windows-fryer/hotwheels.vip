//
// Created by Liga on 6/22/2022.
//

#ifndef HOTWHEELS_BF4_PRE_FRAME_HPP
#define HOTWHEELS_BF4_PRE_FRAME_HPP

#include "../../../../dependencies/sdk/sdk.h"
#include "../../../helpers/vfunc/vfunc.hpp"
#include "../../hooks.hpp"

namespace hooks
{
	using pre_frame_update_t = void ( * )( float );
	inline std::uintptr_t* original_pre_frame_update{ };

	struct pre_frame {
		static void hook_virtual( PDWORD64* table, PBYTE hook, std::size_t index, std::uintptr_t*& original )
		{
			DWORD old_flags{ };
			VirtualProtect( ( void* )( ( *table ) + index ), sizeof( PDWORD64 ), PAGE_EXECUTE_READWRITE, &old_flags );

			original = ( std::uintptr_t* )( *table )[ index ];

			( *table )[ index ] = ( DWORD64 )hook;

			VirtualProtect( ( void* )( ( *table ) + index ), sizeof( PDWORD64 ), old_flags, &old_flags );
		} // pasted :grin:

		static void pre_frame_detour( float delta );

		static void init( )
		{
			hook_virtual( reinterpret_cast< PDWORD64* >( BorderInputNode::GetInstance( )->m_Vtable ), reinterpret_cast< PBYTE >( &pre_frame_detour ),
			              3, original_pre_frame_update );

			console::log( "[HOOKS-VMT] " );

			console::log< fmt::color::cyan >( "Created hook [ {} ]\n", "pre_frame_detour" );
		}

		static void shutdown( )
		{
			std::uintptr_t* buffer{ };

			hook_virtual( reinterpret_cast< PDWORD64* >( BorderInputNode::GetInstance( )->m_Vtable ),
			              reinterpret_cast< PBYTE >( &*original_pre_frame_update ), 3, buffer );
		}
	};
} // namespace hooks
#endif // HOTWHEELS_BF4_PRE_FRAME_HPP
