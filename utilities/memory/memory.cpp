#include "memory.h"
#include "../logging.h"
#include "helpers/pe32.h"

void* mem::get_export_address( const void* module_base, const std::string_view procedure_name )
{
	const std::uint8_t* address = static_cast< const std::uint8_t* >( module_base );
	const IMAGE_DOS_HEADER* dos_header = static_cast< const IMAGE_DOS_HEADER* >( module_base );
	const IMAGE_NT_HEADERS* nt_headers = reinterpret_cast< const IMAGE_NT_HEADERS* >( address + dos_header->e_lfanew );
	const IMAGE_OPTIONAL_HEADER* optional_header = &nt_headers->OptionalHeader;

	const std::uintptr_t export_size = optional_header->DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].Size;
	const std::uintptr_t export_address = optional_header->DataDirectory[ IMAGE_DIRECTORY_ENTRY_EXPORT ].VirtualAddress;

	if ( export_size <= 0U )
		return nullptr;

	const IMAGE_EXPORT_DIRECTORY* pExportDirectory = reinterpret_cast< const IMAGE_EXPORT_DIRECTORY* >( address + export_address );
	const std::uintptr_t* names_rva = reinterpret_cast< const std::uintptr_t* >( address + pExportDirectory->AddressOfNames );
	const std::uintptr_t* functions_rva = reinterpret_cast< const std::uintptr_t* >( address + pExportDirectory->AddressOfFunctions );
	const std::uint16_t* name_ordinals = reinterpret_cast< const std::uint16_t* >( address + pExportDirectory->AddressOfNameOrdinals );

	std::uintptr_t right = pExportDirectory->NumberOfNames;
	std::uintptr_t left = 0;

	while ( right != left )
	{
		const std::uintptr_t middle = left + ( ( right - left ) >> 1U );
		const int iResult = procedure_name.compare( reinterpret_cast< const char* >( address + names_rva[ middle ] ) );

		if ( iResult == 0 )
			return const_cast< void* >( static_cast< const void* >( address + functions_rva[ name_ordinals[ middle ] ] ) );

		if ( iResult > 0 )
			left = middle;
		else
			right = middle;
	}

	logging::push_console_color( FOREGROUND_INTENSE_RED );
	logging::print( _( "[hotwheels] - error - export not found: [{}]" ), procedure_name );
	logging::pop_console_color( );
	return nullptr;
}

void* mem::get_module_base_handle( const std::string_view module_name )
{
	const _PEB32* peb = reinterpret_cast< _PEB32* >( __readfsdword( 0x30 ) );

	if ( module_name.empty( ) )
		return peb->ImageBaseAddress;

	const std::wstring wmodule_name( module_name.begin( ), module_name.end( ) );

	for ( LIST_ENTRY* pListEntry = peb->Ldr->InLoadOrderModuleList.Flink; pListEntry != &peb->Ldr->InLoadOrderModuleList; pListEntry = pListEntry->Flink )
	{
		const _LDR_DATA_TABLE_ENTRY* pEntry = CONTAINING_RECORD( pListEntry, _LDR_DATA_TABLE_ENTRY, InLoadOrderLinks );

		if ( pEntry->BaseDllName.Buffer && wmodule_name.compare( pEntry->BaseDllName.Buffer ) == 0 )
			return pEntry->DllBase;
	}

	logging::push_console_color( FOREGROUND_INTENSE_RED );
	logging::print( _( "[hotwheels] - error - module base not found: [{}]" ), module_name );
	logging::pop_console_color( );
	return nullptr;
}

std::uintptr_t mem::pattern_scan( const std::string_view module_name, const std::string_view signature )
{
	void* module_handle = mem::get_module_base_handle( module_name );

	if ( module_handle == nullptr )
		throw std::runtime_error( std::format( ( "failed to get handle for: {}" ), module_name ) );

	const std::uint8_t* module_address = static_cast< std::uint8_t* >( module_handle );
	const IMAGE_DOS_HEADER* dos_header = static_cast< IMAGE_DOS_HEADER* >( module_handle );
	const IMAGE_NT_HEADERS* nt_headers = reinterpret_cast< const IMAGE_NT_HEADERS* >( module_address + dos_header->e_lfanew );

	return pattern_scan( module_address, nt_headers->OptionalHeader.SizeOfImage, signature );
}

std::uintptr_t mem::pattern_scan( const std::uint8_t* region_start, const std::uintptr_t region_size, const std::string_view signature )
{
	const std::vector<std::optional<std::uint8_t>> vec_bytes = mem::signature_to_bytes( signature );

	for ( std::uintptr_t i = 0U; i < region_size - vec_bytes.size( ); ++i )
	{
		bool byte_found = true;

		for ( std::uintptr_t s = 0U; s < vec_bytes.size( ); ++s )
		{
			if ( vec_bytes[ s ].has_value( ) && region_start[ i + s ] != vec_bytes[ s ].value( ) )
			{
				byte_found = false;
				break;
			}
		}

		if ( byte_found )
			return reinterpret_cast< std::uintptr_t >( &region_start[ i ] );
	}

	logging::push_console_color( FOREGROUND_INTENSE_RED );
	logging::print( _( "[hotwheels] - error - pattern not found: [{}]" ), signature );
	logging::pop_console_color( );
	return 0U;
}

std::vector<std::optional<std::uint8_t>> mem::signature_to_bytes( const std::string_view signature )
{
	std::vector<std::optional<std::uint8_t>> vec_bytes = { };
	auto it_begin = signature.cbegin( );
	const auto it_end = signature.cend( );

	while ( it_begin < it_end )
	{
		if ( *it_begin == '?' )
		{
			if ( ++it_begin; *it_begin == '?' )
				++it_begin;

			vec_bytes.emplace_back( std::nullopt );
		}
		else if ( *it_begin != ' ' )
		{
			std::uint8_t byte = static_cast< std::uint8_t >( ( ( *it_begin >= 'A' ? ( ( ( *it_begin - 'A' ) & ( ~( 'a' ^ 'A' ) ) ) + 10 ) : ( *it_begin <= '9' ? *it_begin - '0' : 0x0 ) ) | 0xF0 ) << 4 );

			if ( ++it_begin; *it_begin != ' ' )
				byte |= static_cast< std::uint8_t >( *it_begin >= 'A' ? ( ( ( *it_begin - 'A' ) & ( ~( 'a' ^ 'A' ) ) ) + 10 ) : ( *it_begin <= '9' ? *it_begin - '0' : 0x0 ) );

			vec_bytes.emplace_back( byte );
		}

		++it_begin;
	}

	return vec_bytes;
}