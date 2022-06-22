//
// Created by Liga on 6/21/2022.
//

#ifndef HOTWHEELS_BF4_ENTRY_HPP
#define HOTWHEELS_BF4_ENTRY_HPP

#include <Windows.h>
#include <iostream>

#include "cheat/global/snakeify.hpp"

namespace entry
{
	struct impl {
		hinstance module_handle;

		void init( );
		void shutdown( );
	};
} // namespace entry

inline entry::impl g_entry;

#endif // HOTWHEELS_BF4_ENTRY_HPP
