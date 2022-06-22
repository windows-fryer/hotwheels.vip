#pragma once
// used: std::any
#include <any>
// used: std::filesystem
#include <filesystem>
// used: std::deque
#include <deque>
// used: std::vector
#include <vector>

// used: winapi includes
#include "../../common.h"
// used: color
#include "../sdk/datatypes/color.h"
// used: fnv1a hashing for variables
#include "../../utilities/encryption/fnv1a.h"

#define c_add_variable( var_type, name, defualt ) const std::uint32_t name = c::add_variable<var_type>(fnv1a::hash_const(#name),fnv1a::hash_const(#var_type), defualt);
#define c_add_variable_vector( var_type, size, name, defualt ) const std::uint32_t name = c::add_variable<std::vector<var_type>>(fnv1a::hash_const(#name), fnv1a::hash_const("std::vector<" #var_type ">"), mem::get_filled_vector<var_type, size>(defualt));
#define c_invalid_variable (std::size_t)(-1)

struct variable_object_t
{
	variable_object_t( const fnv1a_t name_hash, const fnv1a_t type_hash, std::any&& defualt )
		: name_hash( name_hash ), type_hash( type_hash ), var_value( std::move( defualt ) ) { }

	~variable_object_t( ) = default;

	/* get casted variable value */
	template<typename T>
	T& get( )
	{
		return *static_cast< T* >( std::any_cast< T >( &var_value ) );
	}

	/* emplace casted variable value */
	template<typename T>
	void set( T value )
	{
		var_value.emplace<T>( value );
	}

	fnv1a_t name_hash = 0x0;
	fnv1a_t type_hash = 0x0;
	std::any var_value = { };
};

namespace c 
{
	bool init( );
	bool save( std::string_view file_name );
	bool load( std::string_view file_name );
	void remove( const std::size_t index );
	void refresh( );

	std::size_t get_variable_index( const fnv1a_t name_hash );
	std::filesystem::path get_working_path( );

	const std::filesystem::path fs_path = get_working_path( ) / _( "settings" );
	inline std::deque<std::string> vec_file_names = { };
	inline std::vector<variable_object_t> vec_variables = { };
	inline std::string loaded_config_file_name = {};
	inline std::string saved_config_file_name = {};

	template <typename T>
	T& get( const std::uint32_t index )
	{
		return vec_variables.at( index ).get<T>( );
	}

	/* add new configuration variable to massive, and return index of it */
	template <typename T>
	std::uint32_t add_variable( const fnv1a_t name_hash, const fnv1a_t type_hash, const T defualt )
	{
		vec_variables.emplace_back( name_hash, type_hash, std::make_any<T>( defualt ) );
		return vec_variables.size( ) - 1U;
	}
}

struct variables_t
{
	/* menu */
	c_add_variable( color, color_menu_accent, color( 255, 255, 255 ) );
	c_add_variable( bool, menu_fade, true );

	/* logging */
	c_add_variable( color, color_log_prefix, color( 254, 199, 255 ) );
	c_add_variable( bool, log_config_print, false );
	c_add_variable( color, color_log_config_print, color( 255, 255, 255 ) );

	/* misc */
	c_add_variable( bool, custom_netgraph, true );
	c_add_variable( color, color_custom_netgraph, color( 229, 229, 178 ) );
	c_add_variable( bool, misc_discord_rpc, true );

	/* visuals */

	/* world */

	/* screen */

	/* player chams */
	c_add_variable( bool, chams_visible, false );
	c_add_variable( color, chams_visible_color, color(255, 255, 255) );

	c_add_variable( bool, chams_visible_overlay, false );
	c_add_variable( color, chams_visible_overlay_color, color( 255, 255, 255 ) );

	c_add_variable( bool, chams_invisible, false );
	c_add_variable( color, chams_invisible_color, color( 255, 255, 255 ) );

	c_add_variable( bool, chams_invisible_overlay, false );
	c_add_variable( color, chams_invisible_overlay_color, color( 255, 255, 255 ) );

	c_add_variable( int, chams_overlay_material, 0 );

	c_add_variable( int, chams_material, 0 );
	c_add_variable( bool, chams_wireframe, false );
	c_add_variable( bool, chams_render_original, false );

	/* weapon chams */
	c_add_variable( bool, chams_weapon, false );
	c_add_variable( color, chams_weapon_color, color( 255, 255, 255 ) );

	c_add_variable( bool, chams_weapon_overlay, false );
	c_add_variable( color, chams_weapon_overlay_color, color( 255, 255, 255 ) );
	c_add_variable( int, chams_overlay_weapon_material, 0 );

	c_add_variable( int, chams_weapon_material, 0 );
	c_add_variable( bool, chams_weapon_wireframe, false );
	c_add_variable( bool, chams_weapon_render_original, false );

	/* arm chams */
	c_add_variable( bool, chams_arm, false );
	c_add_variable( color, chams_arm_color, color( 255, 255, 255 ) );

	c_add_variable( bool, chams_arm_overlay, false );
	c_add_variable( color, chams_arm_overlay_color, color( 255, 255, 255 ) );
	c_add_variable( int, chams_overlay_arm_material, 0 );

	c_add_variable( int, chams_arm_material, 0 );
	c_add_variable( bool, chams_arm_wireframe, false );
	c_add_variable( bool, chams_arm_render_original, false );

	/* esp */
	c_add_variable( bool, esp_spectators_list, false );
	c_add_variable( color, color_esp_spectators_list_spectating_local, color( 255, 255, 255 ) );
	c_add_variable( color, color_esp_spectators_list_spectating_other, color( 255, 255, 255 ) );

	/* player glow */
	/* entity glow */
	/* misc */
	/* exploits */
	c_add_variable( bool, sv_pure_bypass, false );
	/* movement */
};

inline variables_t vars;