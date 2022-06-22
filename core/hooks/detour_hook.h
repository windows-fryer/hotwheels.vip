#pragma once
#include <format>
#include "../../dependencies/minhook/minhook.h"
#include "../../utilities/encryption/xorstr.h"

class c_detour_hook
{
public:
	c_detour_hook( ) = default;

	explicit c_detour_hook( void* function, void* detour )
		: m_base_fn( function ), m_replace_fn( detour ) { }

	bool install( void* function, void* detour )
	{
		m_base_fn = function;

		if ( m_base_fn == nullptr )
			return false;

		m_replace_fn = detour;

		if ( m_replace_fn == nullptr )
			return false;

		const MH_STATUS status = MH_CreateHook( m_base_fn, m_replace_fn, &m_original_fn );

		if ( status != MH_OK )
			throw std::runtime_error( std::vformat( _( "[hotwheels] - error - failed to create hook function, status: {}\nbase function -> {:#08X}" ), std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_base_fn ) ) ) );

		if ( !this->replace( ) )
			return false;

		return true;
	}

	bool replace( )
	{
		if ( m_base_fn == nullptr )
			return false;

		if ( m_is_hooked )
			return false;

		const MH_STATUS status = MH_EnableHook( m_base_fn );

		if ( status != MH_OK )
			throw std::runtime_error( std::vformat( _( "[hotwheels] - error - failed to enable hook function, status: {}\nbase function -> {:#08X} address" ), std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_base_fn ) ) ) );

		m_is_hooked = true;
		return true;
	}

	bool remove( )
	{
		// restore it at first
		if ( !this->restore( ) )
			return false;

		const MH_STATUS status = MH_RemoveHook( m_base_fn );

		if ( status != MH_OK )
			throw std::runtime_error( std::vformat( _( "[hotwheels] - error - failed to remove hook, status: {}\n base function -> {:#08X} address" ), std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_base_fn ) ) ) );

		return true;
	}

	bool restore( )
	{
		if ( !m_is_hooked )
			return false;

		const MH_STATUS status = MH_DisableHook( m_base_fn );

		if ( status != MH_OK )
			throw std::runtime_error( std::vformat( _( "[hotwheels] - error - failed to restore hook, status: {}\n base function -> {:#08X} address" ), std::make_format_args( MH_StatusToString( status ), reinterpret_cast< std::uintptr_t >( m_base_fn ) ) ) );

		m_is_hooked = false;
		return true;
	}

	template <typename Fn>
	Fn get_original( )
	{
		return static_cast< Fn >( m_original_fn );
	}

	inline bool is_hooked( ) const
	{
		return m_is_hooked;
	}
private:
	bool m_is_hooked = false;
	void* m_base_fn = nullptr;
	void* m_replace_fn = nullptr;
	void* m_original_fn = nullptr;
};