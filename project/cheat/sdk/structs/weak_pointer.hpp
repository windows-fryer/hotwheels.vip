//
// Created by liga on 6/30/2022.
//

#ifndef HOTWHEELS_BF4_WEAK_POINTER_HPP
#define HOTWHEELS_BF4_WEAK_POINTER_HPP

// Frostbite niggery

#include <iostream>
#include <Windows.h>

#include "../../global/snakeify.hpp"

namespace sdk
{
	template< typename T >
	struct weak_token {
		T* real_ptr;
	};

	template< typename T >
	struct weak_ptr {
		weak_token< T >* token;

		T* get_data( )
		{
			__try {
				if ( !this )
					return nullptr;

				if ( !this->token )
					return nullptr;

				if ( !this->token->real_ptr )
					return nullptr;

				return reinterpret_cast< T* >( reinterpret_cast< std::uintptr_t* >( this->token->real_ptr ) - sizeof( void* ) );
			} __except ( exception_execute_handler ) {
				return nullptr;
			}
		}
	};
}

#endif // HOTWHEELS_BF4_WEAK_POINTER_HPP
