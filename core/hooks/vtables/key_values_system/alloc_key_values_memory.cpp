#include "../../hooks.h"
#include "../../../../common.h"

void* __fastcall h::alloc_key_values_memory( void* thisptr, int edx, int size )
{
	static auto original = detours::alloc_key_values_memory.get_original<decltype( &h::alloc_key_values_memory )>( );

	static const std::uintptr_t alloc_key_values_engine = mem::pattern_scan( _( "engine.dll" ), _( "FF 52 04 85 C0 74 0C 56" ) ) + 0x3;
	static const std::uintptr_t alloc_key_values_client = mem::pattern_scan( _( "client.dll" ), _( "FF 52 04 85 C0 74 0C 56" ) ) + 0x3;

	if ( const std::uintptr_t return_address = reinterpret_cast< std::uintptr_t >( _ReturnAddress( ) ); return_address == alloc_key_values_engine || return_address == alloc_key_values_client )
		return nullptr;

	return original( thisptr, edx, size );
}