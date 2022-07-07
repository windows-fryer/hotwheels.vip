//
// Created by liga on 7/1/2022.
//

#include "entry.hpp"
#include "cheat/cheat.hpp"

int main( )
{
#ifndef _DEBUG
	FreeConsole( );
#endif

	cheat::init( );
}