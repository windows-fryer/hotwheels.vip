//
// Created by liga on 7/1/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP
#define HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP

#include <Windows.h>
#include <iostream>

namespace cheat
{
	inline bool requested_shutdown{ };

	inline HMODULE module_handle{ };

	void init( );
	void shutdown( );
} // namespace cheat

#endif // HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP
