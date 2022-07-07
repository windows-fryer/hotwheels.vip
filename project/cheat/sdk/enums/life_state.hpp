//
// Created by liga on 7/6/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_LIFE_STATE_HPP
#define HOTWHEELS_CSGO_EXTERNAL_LIFE_STATE_HPP

namespace sdk
{
	enum life_state {
		life_alive = 0,
		life_dying,
		life_dead,
		life_respawnable,
		life_discardbody
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_LIFE_STATE_HPP
