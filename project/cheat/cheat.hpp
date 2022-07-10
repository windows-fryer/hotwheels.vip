//
// Created by liga on 7/1/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP
#define HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP

#define create_thread( func ) CreateThread( nullptr, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( func ), nullptr, 0, nullptr )

namespace cheat
{
	inline bool requested_shutdown{ };

	void init( );
	void shutdown( );
} // namespace cheat

#endif // HOTWHEELS_CSGO_EXTERNAL_CHEAT_HPP
