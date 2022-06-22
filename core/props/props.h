#pragma once
#include <fstream>
#include <unordered_map>

#include "../../utilities/encryption/fnv1a.h"
#include "../sdk/datatypes/datatable.h"
#include "../sdk/datatypes/datamap.h"
#include "../../common.h"

#define add_variable_offset( var_type, function_name, netvar_name, additional )								\
	[[nodiscard]] std::add_lvalue_reference_t<var_type> function_name()										\
	{																										\
		static constexpr fnv1a_t hashed_netvar = fnv1a::hash_const(netvar_name);										\
		static std::uintptr_t m_offset = c_netvar_manager::get()->map_props[hashed_netvar].m_offset;						\
		return *(std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset + additional);	\
	}

#define add_variable( var_type, function_name, netvar_name ) add_variable_offset( var_type, function_name, netvar_name, 0U )

#define add_pvariable_offset( var_type, function_name, netvar_name, additional )								\
	[[nodiscard]] std::add_pointer_t<var_type> function_name()													\
	{																										\
		static constexpr fnv1a_t hashed_netvar = fnv1a::hash_const(netvar_name);										\
		static std::uintptr_t m_offset = c_netvar_manager::get()->map_props[hashed_netvar].m_offset;						\
		return (std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset + additional);	\
	}

#define add_pvariable( var_type, function_name, netvar_name ) add_pvariable_offset( var_type, function_name, netvar_name, 0U )

#define add_resource_variable( var_type, function_name, netvar_name )														\
	[[nodiscard]] std::add_lvalue_reference_t<var_type> function_name(int index)											\
	{																													\
		static constexpr fnv1a_t hashed_netvar = fnv1a::hash_const(netvar_name);													\
		static std::uintptr_t m_offset = c_netvar_manager::get()->map_props[hashed_netvar].m_offset;									\
		return *(std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset + index * sizeof(var_type));	\
	}

#define add_datafield( var_type, function_name, data_map, data_field )											\
	[[nodiscard]] std::add_lvalue_reference_t<var_type> function_name()										\
	{																										\
		static constexpr fnv1a_t hashed_netvar = fnv1a::hash_const(data_field);										\
		static std::uintptr_t m_offset = c_netvar_manager::get()->find_in_data_map(data_map, hashed_netvar);					\
		return *(std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset);				\
	}

#define add_pdatafield( var_type, function_name, data_map, data_field )											\
	[[nodiscard]] std::add_pointer_t<var_type> function_name()													\
	{																										\
		static constexpr fnv1a_t hashed_netvar = fnv1a::hash_const(data_field);										\
		static std::uintptr_t m_offset = c_netvar_manager::get()->find_in_data_map(data_map, hashed_netvar);					\
		return (std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset);				\
	}

#define add_offset( var_type, function_name, m_offset )														\
	[[nodiscard]] std::add_lvalue_reference_t<var_type> function_name()										\
	{																										\
		return *(std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset);				\
	}

#define add_poffset( var_type, function_name, m_offset )														\
	[[nodiscard]] std::add_pointer_t<var_type> function_name()													\
	{																										\
		return (std::add_pointer_t<var_type>)(reinterpret_cast<std::uintptr_t>(this) + m_offset);				\
	}

class c_recv_prop_hook
{
public:
	c_recv_prop_hook( recv_prop_t* recv_prop, const recv_var_proxy_fn new_proxy_fn ) :
		recv_prop( recv_prop ), original( recv_prop->m_oproxy_fn )
	{
		set_proxy( new_proxy_fn );
	}

	void replace( recv_prop_t* recv_prop )
	{
		this->recv_prop = recv_prop;
		this->original = recv_prop->m_oproxy_fn;
	}

	void restore( ) const
	{
		if ( this->original != nullptr )
			this->recv_prop->m_oproxy_fn = this->original;
	}

	void set_proxy( const recv_var_proxy_fn new_proxy_fn ) const
	{
		this->recv_prop->m_oproxy_fn = new_proxy_fn;
	}

	recv_var_proxy_fn get_original( ) const
	{
		return this->original;
	}
private:
	recv_prop_t* recv_prop = nullptr;
	recv_var_proxy_fn original = nullptr;
};

class c_netvar_manager : public c_singleton<c_netvar_manager>
{
public:
	struct netvar_object_t
	{
		recv_prop_t* m_recv_prop = nullptr;
		std::uintptr_t m_offset = 0U;
	};

	bool init( );

	std::uintptr_t find_in_data_map( data_map_t* data_map, const fnv1a_t field_hash );

	int m_stored_props = 0;
	int m_stored_tables = 0;

	std::unordered_map<fnv1a_t, netvar_object_t> map_props = { };
private:
	void store_props( const char* class_name, recv_table_t* recv_table, const std::uintptr_t offset );
};
