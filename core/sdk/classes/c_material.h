#pragma once
#include "../../../utilities/memory/memory.h"

enum e_material_flag 
{
    material_flag_debug = 1 << 0,
    material_flag_no_debug_override = 1 << 1,
    material_flag_no_draw = 1 << 2,
    material_flag_use_in_fillrate_mode = 1 << 3,
    material_flag_vertex_color = 1 << 4,
    material_flag_vertex_alpha = 1 << 5,
    material_flag_selfillum = 1 << 6,
    material_flag_additive = 1 << 7,
    material_flag_alpha_test = 1 << 8,
    material_flag_multi_pass = 1 << 9,
    material_flag_z_nearer = 1 << 10,
    material_flag_model = 1 << 11,
    material_flag_flat = 1 << 12,
    material_flag_no_cull = 1 << 13,
    material_flag_no_fog = 1 << 14,
    material_flag_ignore_z = 1 << 15,
    material_flag_decal = 1 << 16,
    material_flag_envmap_sphere = 1 << 17,
    material_flag_no_alpha_mod = 1 << 18,
    material_flag_envmap_camera_space = 1 << 19,
    material_flag_base_alpha_envmap_mask = 1 << 20,
    material_flag_translucent = 1 << 21,
    material_flag_normal_map_alpha_envmap_mask = 1 << 22,
    material_flag_needs_software_skinning = 1 << 23,
    material_flag_opaque_texture = 1 << 24,
    material_flag_envmap_mode = 1 << 25,
    material_flag_suppress_decals = 1 << 26,
    material_flag_half_lambert = 1 << 27,
    material_flag_wireframe = 1 << 28,
    material_flag_allow_alpha_to_coverage = 1 << 29,
    material_flag_ignore_alpha_modulation = 1 << 30,
};

class c_material_var
{
public:
    void set( float value )
    {
        return mem::call_vfunc<void>( this, 4, value );
    }   

    void set( int value )
    {
        return mem::call_vfunc<void>( this, 5, value );
    }   

    void set( const char* value )
    {
        return mem::call_vfunc<void>( this, 6, value );
    }
};

class c_material
{
public:
    c_material_var* find_var( const char* name, bool* found, bool complain = true )
    {
        return mem::call_vfunc< c_material_var*>( this, 11, name, found, complain );
    }

    void increment_reference_count( )
    {
        return mem::call_vfunc<void>( this, 12 );
    }

	void set_alpha( float a )
	{
		return mem::call_vfunc<void>( this, 27, a );
	}

	void set_color( float r, float g, float b )
	{
		return mem::call_vfunc<void>( this, 28, r, g, b );
	}	

	void set_flag( int flag, bool state )
	{
		return mem::call_vfunc<void>( this, 29, flag, state );
	}
};