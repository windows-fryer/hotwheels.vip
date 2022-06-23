#ifndef WEDNESDAY_WTF_FNV_HPP
#define WEDNESDAY_WTF_FNV_HPP

#include <iostream>
#include <unordered_map>

constexpr static std::uint32_t default_offset_basis = 0x811C9DC5;
constexpr static std::uint32_t prime                = 0x01000193;

namespace fnv_hashing
{
	inline std::unordered_map< std::uint32_t, std::string > hashes{ };

	template< typename s >
	struct fnv1a;

	template<>
	struct fnv1a< std::uint32_t > {
		constexpr static std::uint32_t hash( char const* string, const std::uint32_t val = default_offset_basis )
		{
			auto temp_hash      = ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );
			hashes[ temp_hash ] = string;

			return temp_hash;
		}

		constexpr static std::uint32_t hash( wchar_t const* string, const std::uint32_t val = default_offset_basis )
		{
			auto temp_hash = ( string[ 0 ] == '\0' ) ? val : hash( &string[ 1 ], ( val ^ std::uint32_t( string[ 0 ] ) ) * prime );

			return temp_hash;
		}
	};
}; // namespace fnv_hashing

using fnv = fnv_hashing::fnv1a< std::uint32_t >;

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
		for ( std::size_t i = 0U; i < strlen( string ); ++i ) {
			hash_value ^= string[ i ];
			hash_value *= u_prime;
		}

		return hash_value;
	}
} // namespace fnv1a

#endif // WEDNESDAY_WTF_FNV_HPP
