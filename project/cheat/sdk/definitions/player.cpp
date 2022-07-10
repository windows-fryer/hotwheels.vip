//
// Created by liga on 7/3/2022.
//

#include "../structs/player.hpp"
#include "../structs/game.hpp"
#include "../structs/offsets.hpp"

#include "../../helpers/driver/driver.hpp"

int sdk::player::flags( )
{
	return driver::read< int >( this + offsets::player_flags );
}

sdk::vector sdk::player::aim_punch_angle( )
{
	return driver::read< sdk::vector >( this + offsets::aim_punch_angle );
}

int sdk::player::default_fov( )
{
	return driver::read< int >( this + offsets::default_fov );
}

sdk::collideable* sdk::player::collideable( )
{
	return reinterpret_cast< sdk::collideable* >( this + offsets::collision );
}

sdk::matrix_3x4 sdk::player::rgfl( )
{
	return driver::read< sdk::matrix_3x4 >( this + offsets::rgfl );
}

int sdk::player::team_id( )
{
	return driver::read< int >( this + offsets::team_id );
}

sdk::life_state sdk::player::life_state( )
{
	return static_cast< sdk::life_state >( driver::read< int >( this + offsets::life_state ) );
}

bool sdk::player::dormant( )
{
	return driver::read< bool >( this + offsets::dormant );
}

bool sdk::player::spotted_by_mask( )
{
	return driver::read< bool >( this + offsets::spotted_by_mask );
}

sdk::player_info sdk::player::player_info( )
{
	static auto engine_dll = driver::base_address( "engine.dll" );

	auto client_state = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::client_state ) );
	auto user_info    = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( client_state + offsets::user_info ) );
	auto items        = driver::read< std::uint32_t >(
        reinterpret_cast< PVOID >( driver::read< std::uint32_t >( reinterpret_cast< PVOID >( user_info + 0x40 ) ) + 0xC ) );

	return driver::read< sdk::player_info >(
		reinterpret_cast< PVOID >( driver::read< std::uint32_t >( reinterpret_cast< PVOID >( items + 0x28 + ( index( ) - 1 ) * 0x34 ) ) ) );
}

int sdk::player::index( )
{
	return driver::read< int >( this + offsets::entity_index );
}

int sdk::player::health( )
{
	return driver::read< int >( this + offsets::player_health );
}

std::string_view sdk::player::competitive_rank( )
{
	static auto engine_dll = driver::base_address( "client.dll" );

	auto resource = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( engine_dll + offsets::player_resource ) );

	if ( !resource )
		return { "Unranked" };

	auto rank = driver::read< std::uint32_t >( reinterpret_cast< PVOID >( resource + offsets::competitive_rank + ( index( ) * 0x4 ) ) );

	const char* rank_names[] = { "Unranked",
		                         "Silver I",
		                         "Silver II",
		                         "Silver III",
		                         "Silver IV",
		                         "Silver Elite",
		                         "Silver Elite Master",
		                         "Gold Nova I",
		                         "Gold Nova II",
		                         "Gold Nova III",
		                         "Gold Nova Master",
		                         "Master Guardian I",
		                         "Master Guardian II",
		                         "Master Guardian Elite",
		                         "Distinguished Master Guardian",
		                         "Legendary Eagle",
		                         "Legendary Eagle Master",
		                         "Supreme Master First Class",
		                         "The Global Elite" };

	if ( rank > 18 )
		return { "Broken Rank" };

	return std::string_view( rank_names[ rank ] );
}

int sdk::player::money( )
{
	return driver::read< int >( this + offsets::account );
}

sdk::weapon* sdk::player::get_weapon( int index )
{
	auto weapon_index = driver::read< int >( this + offsets::my_weapons + ( index * 0x4 ) ) & 0xFFF;

	return reinterpret_cast< sdk::weapon* >( sdk::game::get_entity( weapon_index - 1 ) );
}

sdk::weapon* sdk::player::get_weapon( )
{
	auto weapon_index = driver::read< int >( this + offsets::active_weapon ) & 0xFFF;

	return reinterpret_cast< sdk::weapon* >( sdk::game::get_entity( weapon_index - 1 ) );
}

sdk::weapon_info sdk::player::get_weapon_info( )
{
	auto weapon = get_weapon( );

	if ( !weapon )
		return { };

	return weapon->weapon_info( );
}