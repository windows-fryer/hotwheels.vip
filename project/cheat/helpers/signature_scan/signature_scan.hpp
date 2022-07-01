//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_SIGNATURE_SCAN_HPP
#define HOTWHEELS_BF4_SIGNATURE_SCAN_HPP

#include <iostream>
#include <vector>

namespace signature_scan
{
	struct address {
	public:
		std::uintptr_t m_address{ };

	public:
		constexpr address( ) : m_address{ 0 } { };

		address( std::uintptr_t ad ) : m_address{ ad } { };

		address( void* address ) : m_address{ reinterpret_cast< std::uintptr_t >( address ) } { };

		operator std::uintptr_t( ) const
		{
			return m_address;
		}

		operator void*( ) const
		{
			return reinterpret_cast< void* >( m_address );
		}

		template< typename T = address >
		T to( ) const
		{
			return *( T* )( m_address );
		}

		template< typename T = address >
		T as( ) const
		{
			return m_address ? ( T )( m_address ) : T( );
		}

		template< typename T = address >
		T at( std::ptrdiff_t offset ) const
		{
			return m_address ? *( T* )( m_address + offset ) : T( );
		}

		template< typename T = address >
		T add( std::ptrdiff_t offset ) const
		{
			return m_address ? ( T )( m_address + offset ) : T( );
		}

		template< typename T = address >
		T sub( std::ptrdiff_t offset ) const
		{
			return m_address ? ( T )( m_address - offset ) : T( );
		}

		template< typename T = address >
		T get( std::uint8_t dereferences = 1 ) const
		{
			if ( !m_address )
				return T( );

			auto addr = m_address;

			while ( dereferences-- )
				if ( addr )
					addr = *reinterpret_cast< std::uintptr_t* >( addr );

			return ( T )( addr );
		}

		template< typename T = std::uintptr_t >
		void set( const T& value )
		{
			if ( !m_address )
				return;

			*( T* )( m_address ) = value;
		}

		template< typename T = address >
		T relative( std::ptrdiff_t offset = 0x1 ) const
		{
			if ( !m_address )
				return T( );

			const std::uintptr_t new_address = m_address + offset;

			const auto relative_offset = *reinterpret_cast< std::int32_t* >( new_address );
			if ( !relative_offset )
				return T( );

			return ( T )( new_address + sizeof( std::int32_t ) + relative_offset );
		}
	};

	struct impl {
	public:
		std::uintptr_t find_pattern( std::uint8_t* region_start, std::uintptr_t region_size, const char* pattern )
		{
			std::vector< int > vec_bytes = pattern_to_bytes( pattern );
			for ( unsigned long i = 0UL; i < region_size - vec_bytes.size( ); ++i ) {
				bool byte_found = true;
				for ( unsigned long s = 0UL; s < vec_bytes.size( ); ++s ) {
					if ( region_start[ i + s ] != vec_bytes[ s ] && vec_bytes[ s ] != -1 ) {
						byte_found = false;
						break;
					}
				}

				if ( byte_found )
					return reinterpret_cast< std::uintptr_t >( &region_start[ i ] );
			}
			return 0U;
		}

		std::vector< int > pattern_to_bytes( const char* pattern )
		{
			std::vector< int > vec_bytes = { };
			char* start                  = const_cast< char* >( pattern );
			char* end                    = start + strlen( pattern );

			for ( char* current = start; current < end; ++current ) {
				if ( *current == '?' ) {
					++current;

					if ( *current == '?' )
						++current;

					vec_bytes.push_back( -1 );
				} else
					// convert byte to hex
					vec_bytes.push_back( strtoul( current, &current, 16 ) );
			}

			return vec_bytes;
		}
	};
} // namespace signature_scan

inline signature_scan::impl g_signature_scan;

#endif // HOTWHEELS_BF4_SIGNATURE_SCAN_HPP
