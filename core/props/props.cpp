#include "props.h"

#include "../sdk/interfaces/interfaces.h"

bool c_netvar_manager::init(  )
{
	map_props.clear( );
	m_stored_props = 0;
	m_stored_tables = 0;

	for ( auto client_class = i::client->get_all_classes( ); client_class != nullptr; client_class = client_class->m_next )
	{
		if ( client_class->m_recv_table == nullptr )
			continue;

		store_props( client_class->m_network_name, client_class->m_recv_table, 0U );
	}

	return !map_props.empty( );
}

void c_netvar_manager::store_props( const char* class_name, recv_table_t* recv_table, const std::uintptr_t offset )
{
	const fnv1a_t class_hash = fnv1a::hash( class_name );
	const fnv1a_t delimiter_hash = fnv1a::hash( "->", class_hash );
	const fnv1a_t base_class_hash = fnv1a::hash( "baseclass", delimiter_hash );

	for ( int i = 0; i < recv_table->m_nprops; ++i )
	{
		const auto current_prop = &recv_table->m_pprops[ i ];

		if ( current_prop == nullptr || isdigit( current_prop->m_var_name[ 0 ] ) )
			continue;

		const fnv1a_t total_hash = fnv1a::hash( current_prop->m_var_name, delimiter_hash );

		if ( total_hash == base_class_hash )
			continue;

		if ( const auto child_table = current_prop->m_data_table; child_table != nullptr &&
			child_table->m_nprops > 0 &&
			child_table->m_net_table_name[ 0 ] == 'D' &&
			current_prop->m_recv_type == dpt_datatable )
			store_props( class_name, child_table, static_cast< std::uintptr_t >( current_prop->m_offset ) + offset );

		const std::uintptr_t uTotalOffset = static_cast< std::uintptr_t >( current_prop->m_offset ) + offset;

		if ( !map_props[ total_hash ].m_offset )
		{
			map_props[ total_hash ] = { current_prop, uTotalOffset };

			m_stored_props++;
		}
	}

	m_stored_tables++;
}

std::uintptr_t c_netvar_manager::find_in_data_map( data_map_t* data_map, const fnv1a_t field_hash )
{
	while ( data_map != nullptr )
	{
		for ( int i = 0; i < data_map->m_data_fields; i++ )
		{
			if ( data_map->m_data_desc[ i ].m_field_name == nullptr )
				continue;

			if ( fnv1a::hash( data_map->m_data_desc[ i ].m_field_name ) == field_hash )
				return data_map->m_data_desc[ i ].m_field_offset[ td_offset_normal ];

			if ( data_map->m_data_desc[ i ].m_field_type == field_embedded )
			{
				if ( data_map->m_data_desc[ i ].m_type_description != nullptr )
				{
					if ( const auto offset = find_in_data_map( data_map->m_data_desc[ i ].m_type_description, field_hash ); offset != 0U )
						return offset;
				}
			}
		}

		data_map = data_map->m_base_map;
	}

	return 0U;
}
