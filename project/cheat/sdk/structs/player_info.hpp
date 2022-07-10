//
// Created by liga on 7/6/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_PLAYER_INFO_HPP
#define HOTWHEELS_CSGO_EXTERNAL_PLAYER_INFO_HPP

#include <iostream>

namespace sdk
{
	struct player_info {
	private:
		std::int64_t pad; // 2 statics for some fucking reason...

	public:
		int xuidlow;
		int xuidhigh;

		char name[ 128 ]{ };
		int user_id{ };
		char steam_id[ 20 ]{ };

	private:
		char pad_2[0x10];

	public:
		unsigned int friends_id_32;
		char friends_name[ 128 ];
		bool fake_player;
		bool is_hltv;

		unsigned int custom_files[ 4 ];
		unsigned char files_downloaded;
	};
} // namespace sdk

#endif // HOTWHEELS_CSGO_EXTERNAL_PLAYER_INFO_HPP
