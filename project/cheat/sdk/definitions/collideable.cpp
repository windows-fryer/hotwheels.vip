//
// Created by liga on 7/5/2022.
//

#include "../structs/collideable.hpp"
#include "../structs/offsets.hpp"

#include "../../helpers/driver/driver.hpp"

sdk::vector sdk::collideable::mins( )
{
	return driver::read< sdk::vector >( this + 0x8 );
}

sdk::vector sdk::collideable::maxs( )
{
	return driver::read< sdk::vector >( this + 0x8 + sizeof( sdk::vector ) );
}