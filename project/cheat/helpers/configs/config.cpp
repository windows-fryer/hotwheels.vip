//
// Created by liga on 7/2/2022.
//

#include "config.hpp"

#include <fstream>

void config::impl::save( std::string path )
{
	using namespace nlohmann;

	json reader;

	for ( auto& setting : settings ) {
		switch ( setting.second.type ) {
		case variable_type::VARIABLE_BOOL:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.bool_value;
			break;
		case variable_type::VARIABLE_INT:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.int_value;
			break;

		case variable_type::VARIABLE_FLOAT:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.float_value;
			break;

		case variable_type::VARIABLE_COLOR:
			reader[ fnv_hashing::hashes[ setting.first ] ] = { setting.second.color_value.x, setting.second.color_value.y,
				                                               setting.second.color_value.z, setting.second.color_value.w };
			break;

		case variable_type::VARIABLE_STRING:
			reader[ fnv_hashing::hashes[ setting.first ] ] = setting.second.string_value;
			break;
		}
	}

	std::ofstream stream( path );

	stream << std::setw( 4 ) << reader << std::endl;

	stream.close( );
}

void config::impl::load( std::string path )
{
	using namespace nlohmann;

	json reader{ };

	std::ifstream stream( path );

	if ( !stream )
		return;

	stream >> reader;

	stream.close( );

	for ( auto& setting : settings ) {
		if ( !fnv_hashing::hashes[ setting.first ].data( ) )
			continue;

		if ( !reader.contains( fnv_hashing::hashes[ setting.first ] ) )
			continue;

		switch ( setting.second.type ) {
		case variable_type::VARIABLE_BOOL:
			setting.second.bool_value = reader[ fnv_hashing::hashes[ setting.first ] ];
			break;
		case variable_type::VARIABLE_INT:
			setting.second.int_value = reader[ fnv_hashing::hashes[ setting.first ] ];
			break;

		case variable_type::VARIABLE_FLOAT:
			setting.second.float_value = reader[ fnv_hashing::hashes[ setting.first ] ];
			break;

		case variable_type::VARIABLE_COLOR:
			setting.second.color_value.x = reader[ fnv_hashing::hashes[ setting.first ] ][ 0 ];
			setting.second.color_value.y = reader[ fnv_hashing::hashes[ setting.first ] ][ 1 ];
			setting.second.color_value.z = reader[ fnv_hashing::hashes[ setting.first ] ][ 2 ];
			setting.second.color_value.w = reader[ fnv_hashing::hashes[ setting.first ] ][ 3 ];

			break;

		case variable_type::VARIABLE_STRING:
			setting.second.string_value = reader[ fnv_hashing::hashes[ setting.first ] ];

			break;
		}
	}
}

void config::impl::insert( std::uint32_t hash, option _option )
{
	settings.insert( std::make_pair( hash, _option ) );
}

void config::impl::insert( std::string string, option _option )
{
	settings.insert( std::make_pair( fnv( string.c_str( ) ), _option ) );
}

void config::impl::init( )
{
	insert( "menu_open_smooth", true );

	insert( "aimbot_rcs", false );
	insert( "aimbot_rcs_x", 100.f );
	insert( "aimbot_rcs_y", 100.f );
	insert( "aimbot_rcs_smooth", 0.f );
	insert( "aimbot_rcs_error", true );

	insert( "visuals_boxes", false );
	insert( "visuals_boxes_color", ImVec4( 1.f, 1.f, 1.f, 1.f ) );
	insert( "visuals_names", false );
	insert( "visuals_names_color", ImVec4( 1.f, 1.f, 1.f, 1.f ) );
	insert( "visuals_weapons", false );
	insert( "visuals_weapons_icons", false );
	insert( "visuals_weapons_color", ImVec4( 1.f, 1.f, 1.f, 1.f ) );
	insert( "visuals_health_bars", false );
	insert( "visuals_health_bars_color", ImVec4( 0.f, 1.f, 0.f, 1.f ) );

	insert( "visuals_recoil_crosshair", false );
	insert( "visuals_recoil_crosshair_color", ImVec4( 1.f, 1.f, 1.f, 1.f ) );

	insert( "movement_bunny_hop", false );
}
