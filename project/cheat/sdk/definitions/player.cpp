//
// Created by liga on 7/3/2022.
//

#include "../structs/player.hpp"
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
