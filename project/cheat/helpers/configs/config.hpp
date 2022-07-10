//
// Created by liga on 7/2/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_CONFIG_HPP
#define HOTWHEELS_CSGO_EXTERNAL_CONFIG_HPP

#include <deque>

#include "../../../dependencies/fnv/fnv.hpp"
#include "../../../dependencies/imgui/imgui.h"
#include "../../../dependencies/json/json.hpp"

namespace config
{
	enum class variable_type : int {
		VARIABLE_BOOL,
		VARIABLE_INT,
		VARIABLE_FLOAT,
		VARIABLE_COLOR,
		VARIABLE_STRING
	};

	struct option {
		variable_type type{ };

		bool bool_value{ };

		int int_value{ };

		float float_value{ };

		ImVec4 color_value{ };

		std::string string_value{ };

		option( bool value )
		{
			this->type       = variable_type::VARIABLE_BOOL;
			this->bool_value = value;
		}

		option( int value )
		{
			this->type      = variable_type::VARIABLE_INT;
			this->int_value = value;
		}

		option( float value )
		{
			this->type        = variable_type::VARIABLE_FLOAT;
			this->float_value = value;
		}

		option( ImVec4 value )
		{
			this->type        = variable_type::VARIABLE_COLOR;
			this->color_value = value;
		}

		option( std::string value )
		{
			this->type         = variable_type::VARIABLE_STRING;
			this->string_value = value;
		}
	};

	struct impl {
		std::unordered_map< std::int32_t, option > settings{ };

		void init( );

		void save( std::string path );
		void load( std::string path );

		void insert( std::uint32_t hash, option _option );
		void insert( std::string name, option _option );

		template< typename T >
		T& find( std::uint32_t hash )
		{
			auto found_option = settings.find( hash );

			if ( !found_option._Ptr )
				return ( T& )( nullptr );

			switch ( found_option->second.type ) {
			case variable_type::VARIABLE_BOOL:
				return ( T& )( found_option->second.bool_value );
			case variable_type::VARIABLE_INT:
				return ( T& )( found_option->second.int_value );
			case variable_type::VARIABLE_FLOAT:
				return ( T& )( found_option->second.float_value );
			case variable_type::VARIABLE_COLOR:
				return ( T& )( found_option->second.color_value );
			case variable_type::VARIABLE_STRING:
				return ( T& )( found_option->second.string_value );
			}

			return ( T& )( nullptr );
		}

		template< typename T >
		T* find( std::string name )
		{
			auto found_option = settings.find( fnv( name.c_str( ) ) );

			if ( !found_option._Ptr )
				return ( T* )( nullptr );

			switch ( found_option->second.type ) {
			case variable_type::VARIABLE_BOOL:
				return ( T* )( &found_option->second.bool_value );
			case variable_type::VARIABLE_INT:
				return ( T* )( &found_option->second.int_value );
			case variable_type::VARIABLE_FLOAT:
				return ( T* )( &found_option->second.float_value );
			case variable_type::VARIABLE_COLOR:
				return ( T* )( &found_option->second.color_value );
			case variable_type::VARIABLE_STRING:
				return ( T* )( &found_option->second.string_value );
			}

			return ( T* )( nullptr );
		}
	};
} // namespace config

inline config::impl g_config;

#endif // HOTWHEELS_CSGO_EXTERNAL_CONFIG_HPP
