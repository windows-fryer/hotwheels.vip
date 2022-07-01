//
// Created by liga on 6/29/2022.
//

#ifndef HOTWHEELS_BF4_MODULES_HPP
#define HOTWHEELS_BF4_MODULES_HPP

#include "../../global/snakeify.hpp"
#include "../signature_scan/signature_scan.hpp"

#include <Windows.h>
#include <string>

namespace modules
{
	struct module {
	public:
		module( ) = default;

		module( std::string_view module_name )
		{
			this->module_name = module_name;

			do {
				module_handle = get_module_handle( module_name.data( ) );
			} while ( !module_handle );
		}

		signature_scan::address pattern_scan( std::string_view sig )
		{
			const auto module_address = reinterpret_cast< std::uint8_t* >( module_handle );
			const auto dos_header     = reinterpret_cast< PIMAGE_DOS_HEADER >( module_handle );
			const auto nt_headers     = reinterpret_cast< PIMAGE_NT_HEADERS >( module_address + dos_header->e_lfanew );

			return g_signature_scan.find_pattern( module_address, nt_headers->OptionalHeader.SizeOfImage, sig.data( ) );
		}
		std::string get_module_name( )
		{
			return module_name;
		}

		HMODULE& unsafe_get_handle( )
		{
			return module_handle;
		}

		HMODULE get_handle( )
		{
			return module_handle;
		}

	private:
		HMODULE module_handle{ };
		std::string module_name{ };
	};

	void init( );
	void shutdown( );

} // namespace modules

inline modules::module g_game{ };

#endif // HOTWHEELS_BF4_MODULES_HPP
