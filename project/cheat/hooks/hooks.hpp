//
// Created by Liga on 6/22/2022.
//

#ifndef HOTWHEELS_BF4_HOOKS_HPP
#define HOTWHEELS_BF4_HOOKS_HPP

#include "../../dependencies/fmt/core.h"

#include <iostream>

#include "../../dependencies/minhook/MinHook.h"
#include "../helpers/console/console.hpp"

namespace hooks
{
	template< class T, class R >
	struct hook_helper {
	private:
		void* source;
		void* original;

	public:
		void create( auto source, auto destination, const char* name = "undefined" )
		{
			if ( MH_CreateHook( ( void* )source, ( void* )destination, &original ) != MH_OK ) {
				console::log( "[HOOKS] " );

				console::log< fmt::color::red >( "Failed to create hook [ {} ]\n", name );

				return;
			}

			this->source = source;

			console::log( "[HOOKS] " );

			console::log< fmt::color::cyan >( "Created hook [ {} ]\n", name );
		}

		void disable( )
		{
			MH_DisableHook( source );
		}

		template< typename... ARGS >
		R call_original( ARGS&&... arguments )
		{
			return ( R )( reinterpret_cast< T* >( original )( arguments... ) );
		}
	};

	struct impl {
	public:
		void init( );
		void shutdown( );
	};
} // namespace hooks

inline hooks::impl g_hooks;

#define CREATE_HOOK_HELPER( name, args, rtn ) inline hook_helper< args, rtn > name;

#endif // HOTWHEELS_BF4_HOOKS_HPP
