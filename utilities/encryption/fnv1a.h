#pragma once
using fnv1a_t = std::uint32_t;

namespace fnv1a
{
	constexpr std::uint32_t u_basis = 0x811C9DC5;
	constexpr std::uint32_t u_prime = 0x1000193;

	consteval fnv1a_t hash_const( const char* string, const fnv1a_t hash_value = u_basis ) noexcept
	{
		return ( string[ 0 ] == '\0' ) ? hash_value : hash_const( &string[ 1 ], ( hash_value ^ static_cast< fnv1a_t >( string[ 0 ] ) ) * u_prime );
	}

	inline fnv1a_t hash( const char* string, fnv1a_t hash_value = u_basis )
	{
		for ( std::size_t i = 0U; i < strlen( string ); ++i )
		{
			hash_value ^= string[ i ];
			hash_value *= u_prime;
		}

		return hash_value;
	}
}
