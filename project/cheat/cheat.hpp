//
// Created by Liga on 6/21/2022.
//

#ifndef HOTWHEELS_BF4_CHEAT_HPP
#define HOTWHEELS_BF4_CHEAT_HPP

namespace cheat
{
	struct impl {
		static void init( );
		static void shutdown( );
	};
} // namespace cheat

inline cheat::impl g_cheat;

#endif // HOTWHEELS_BF4_CHEAT_HPP
