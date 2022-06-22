#pragma once
#include <cstddef>
#include <string_view>
#include <vector>
#include <optional>

namespace mem
{
	template <typename T = void*>
	constexpr T get_vfunc( void* thisptr, std::size_t index )
	{
		return ( *static_cast< T** >( thisptr ) )[ index ];
	}

	template <typename T, typename ... Args_t>
	constexpr T call_vfunc( void* thisptr, std::size_t index, Args_t... arg_list )
	{
		using original = T( __thiscall* )( void*, decltype( arg_list )... );
		return ( *static_cast< original** >( thisptr ) )[ index ]( thisptr, arg_list... );
	}

	template <typename T>
	static auto relative_to_absolute( const T& address )
	{
		return address + 4 + *reinterpret_cast< int* >( address );
	}

	template <typename T, std::size_t S>
	std::vector<T> get_filled_vector( const T& fill )
	{
		std::vector<T> vec_temp( S );
		std::fill( vec_temp.begin( ), vec_temp.begin( ) + S, fill );
		return vec_temp;
	}

	void* get_module_base_handle( const std::string_view module_name );
	void* get_export_address( const void* module_base, const std::string_view procedure_name );

	std::uintptr_t pattern_scan( const std::string_view module_name, const std::string_view signature );
	std::uintptr_t pattern_scan( const std::uint8_t* region_start, const std::uintptr_t region_size, const std::string_view signature );
	std::vector<std::optional<std::uint8_t>> signature_to_bytes( const std::string_view signature );
}