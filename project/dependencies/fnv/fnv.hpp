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

#endif // WEDNESDAY_WTF_FNV_HPP
