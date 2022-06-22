#pragma once

#include <limits>
#include <xutility>

template< typename t >
struct bit_flag_t
{
	bit_flag_t( ) = default;
	explicit bit_flag_t( const t& value ) : m_value( value ) { };

	constexpr bool has( const t& value ) const
	{
		return m_value & value;
	};

	constexpr bool has_any_of( std::initializer_list< t > lst )
	{
		return std::find( std::begin( lst ), std::end( lst ), m_value ) != std::end( lst );
	};

	constexpr void add( const t& value )
	{
		m_value |= value;
	};

	constexpr void remove( const t& value )
	{
		m_value &= ~value;
	}

	constexpr void clear( )
	{
		m_value = { };
	};

	constexpr bool is_empty( ) const
	{
		return m_value == std::numeric_limits< t >::quiet_NaN( );
	};

	constexpr operator t( ) const
	{
		return m_value;
	};

	// equality check operator
	constexpr bit_flag_t< t >& operator=( const bit_flag_t< t >& value )
	{
		m_value = value.m_value;

		return *this;
	};

	constexpr t& operator=( const t& value )
	{
		m_value = value;

		return m_value;
	}

	t m_value = { };
};