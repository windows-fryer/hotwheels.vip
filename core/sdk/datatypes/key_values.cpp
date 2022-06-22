#include "key_values.h"
#include "../../sdk/interfaces/interfaces.h"
#include "../../../utilities/encryption/xorstr.h"
#include <cassert>

c_key_values::c_key_values( const char* key_name )
{
	static auto original = reinterpret_cast< void( __thiscall* )( void*, const char* ) >( mem::pattern_scan( _("client.dll"), _( "55 8B EC 51 33 C0 C7 45" ) ) ); // @xref: "OldParticleSystem_Destroy"
	assert( original != nullptr );

	original( this, key_name );
}

void* c_key_values::operator new( std::size_t allocation_size )
{
	return i::key_values_system->alloc_key_values_memory( allocation_size );
}

void c_key_values::operator delete( void* memory )
{
	i::key_values_system->free_key_values_memory( memory );
}

c_key_values* c_key_values::from_string( const char* name, const char* value )
{
	static auto original = mem::pattern_scan( _("client.dll" ), _( "55 8B EC 81 EC ? ? ? ? 85 D2 53" ) );
	c_key_values* key_values = nullptr;

	if ( original == 0U )
		return nullptr;

	__asm
	{
		push 0
		mov edx, value
		mov ecx, name
		call original
		add esp, 4
		mov key_values, eax
	}

	return key_values;
}

void c_key_values::load_from_buffer( char const* szResourceName, const char* szBuffer, void* pFileSystem, const char* szPathID, get_symbol_proc_fn pfnEvaluateSymbolProc )
{
	static auto original = reinterpret_cast< void( __thiscall* )( void*, const char*, const char*, void*, const char*, void*, void* ) >( mem::pattern_scan( _("client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89" ) ) ); // @xref: "KeyValues::LoadFromBuffer(%s%s%s): Begin"
	assert( original != nullptr );

	original( this, szResourceName, szBuffer, pFileSystem, szPathID, pfnEvaluateSymbolProc, nullptr );
}

bool c_key_values::load_from_file( void* file_system, const char* szResourceName, const char* szPathID, get_symbol_proc_fn pfnEvaluateSymbolProc )
{
	static auto original = reinterpret_cast< bool( __thiscall* )( void*, void*, const char*, const char*, void* ) >( mem::pattern_scan( _("client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 14 53 56 8B 75 08 57 FF" ) ) ); // @xref: "rb"
	assert( original != nullptr );

	return original( this, file_system, szResourceName, szPathID, pfnEvaluateSymbolProc );
}

c_key_values* c_key_values::find_key( const char* key_name, const bool create )
{
	using FindKeyFn = c_key_values * ( __thiscall* )( void*, const char*, bool );
	static auto original = reinterpret_cast< FindKeyFn >( mem::pattern_scan( _("client.dll" ), _( "55 8B EC 83 EC 1C 53 8B D9 85 DB" ) ) );
	assert( original != nullptr );

	return original( this, key_name, create );
}

int c_key_values::get_int( const char* key_name, const int default_value )
{
	if ( c_key_values* sub_key = find_key( key_name, false ); sub_key != nullptr )
	{
		switch ( sub_key->chType )
		{
		case type_string:
			return std::atoi( sub_key->m_value );
		case type_wstring:
			return _wtoi( sub_key->m_wvalue );
		case type_float:
			return static_cast< int >( sub_key->m_flvalue );
		case type_uint64:
			assert( 0 );
			return 0;
		case type_int:
		case type_ptr:
		default:
			return sub_key->m_ivalue;
		}
	}

	return default_value;
}

float c_key_values::get_float( const char* key_name, const float default_value )
{
	if ( c_key_values* sub_key = find_key( key_name, false ); sub_key != nullptr )
	{
		switch ( sub_key->chType )
		{
		case type_string:
			return static_cast< float >( std::atof( sub_key->m_value ) );
		case type_wstring:
			return std::wcstof( sub_key->m_wvalue, nullptr );
		case type_float:
			return sub_key->m_flvalue;
		case type_int:
			return static_cast< float >( sub_key->m_ivalue );
		case type_uint64:
			return static_cast< float >( *reinterpret_cast< std::uint64_t* >( sub_key->m_value ) );
		case type_ptr:
		default:
			return 0.0f;
		}
	}

	return default_value;
}

const char* c_key_values::get_string( const char* key_name, const char* default_value )
{
	static auto original = reinterpret_cast< const char* ( __thiscall* )( void*, const char*, const char* ) >( mem::pattern_scan( _("client.dll" ), _( "55 8B EC 83 E4 C0 81 EC ? ? ? ? 53 8B 5D 08" ) ) );
	assert( original != nullptr );

	return original( this, key_name, default_value );
}

void c_key_values::set_string( const char* key_name, const char* string_value )
{
	c_key_values* sub_key = find_key( key_name, true );

	if ( sub_key == nullptr )
		return;

	static auto original = reinterpret_cast< void( __thiscall* )( void*, const char* ) >( mem::pattern_scan( _("client.dll" ), _( "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01" ) ) );
	assert( original != nullptr );

	original( sub_key, string_value );
}

void c_key_values::set_int( const char* key_name, const int value )
{
	c_key_values* sub_key = find_key( key_name, true );

	if ( sub_key == nullptr )
		return;

	sub_key->m_ivalue = value;
	sub_key->chType = type_int;
}

void c_key_values::set_uint64( const char* key_name, const int low_value, const int high_value )
{
	c_key_values* sub_key = find_key( key_name, true );

	if ( sub_key == nullptr )
		return;

	delete[ ] sub_key->m_value;

	delete[ ] sub_key->m_wvalue;
	sub_key->m_wvalue = nullptr;

	sub_key->m_value = new char[ sizeof( std::uint64_t ) ];
	*reinterpret_cast< std::uint64_t* >( sub_key->m_value ) = static_cast< std::uint64_t >( high_value ) << 32ULL | low_value;
	sub_key->chType = type_uint64;
}
