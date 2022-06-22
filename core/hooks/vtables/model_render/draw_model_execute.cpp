#include "../../hooks.h"
#include "../../../cfg/config.h"
#include "../../../sdk/classes/entity.h"
#include "../../../sdk/structs/models.hpp"
#include "../../../sdk/interfaces/interfaces.h"

/*
		* @note: materials info:
		1	shaders: https://developer.valvesoftware.com/wiki/Category:Shaders
		-		parameters: https://developer.valvesoftware.com/wiki/Category:List_of_Shader_Parameters
		2	proxies: https://developer.valvesoftware.com/wiki/Material_proxies
		-		list: https://developer.valvesoftware.com/wiki/List_Of_Material_Proxies
		*
		* use "mat_texture_list 1" command to see full materials list
*/

enum e_draw_model_flags : unsigned int
{
	studio_none = 0x00000000,
	studio_render = 0x00000001,
	studio_viewxformattachments = 0x00000002,
	studio_drawtranslucentsubmodels = 0x00000004,
	studio_twopass = 0x00000008,
	studio_static_lighting = 0x00000010,
	studio_wireframe = 0x00000020,
	studio_item_blink = 0x00000040,
	studio_noshadows = 0x00000080,
	studio_wireframe_vcollide = 0x00000100,
	studio_nolighting_or_cubemap = 0x00000200,
	studio_skip_flexes = 0x00000400,
	studio_donotmodifystencilstate = 0x00000800,
	studio_skip_decals = 0x10000000,
	studio_shadowtexture = 0x20000000,
	studio_shadowdepthtexture = 0x40000000,
	studio_transparency = 0x80000000
};

c_material* create_custom_material( const char* name, const char* shader, const char* material )
{
	c_key_values* key_values = new c_key_values( name );

	/* loading the keyvalues into mem */
	key_values->load_from_buffer( name, material );

	return i::material_system->create_material( name, key_values );
}

void __fastcall h::draw_model_execute( int ecx, int edx, void* ctx, void* state, model_render_info_t* info, math::c_matrix3x4* matrix )
{
	static auto original = detours::draw_model_execute.get_original<decltype( &h::draw_model_execute )>( );

	SEH_START

		if ( !i::engine_client->in_game( ) || i::engine_client->is_taking_screenshot( ) )
			return original( ecx, edx, ctx, state, info, matrix );

	if ( i::model_render->is_forced_material_override( ) )
		return original( ecx, edx, ctx, state, info, matrix );

	static c_material* textured = nullptr;
	static c_material* flat = nullptr;
	static c_material* glow = nullptr;
	static c_material* snow = nullptr;

	if ( !textured || !flat || !glow || !snow )
	{
		textured = i::material_system->find_material( _( "debug/debugambientcube" ) );
		flat = i::material_system->find_material( _( "debug/debugdrawflat" ) );
		glow = create_custom_material( _( "hw_glow_material" ), _( "VertexLitGeneric" ),
			_( R"("VertexLitGeneric" {
	"$additive" "1"
	"$envmap" "models/effects/cube_white"
	"$envmaptint" "[1 1 1]"
	"$envmapfresnel" "1"
	"$envmapfresnelminmaxexp" "[0 1 2]"
	"$alpha" "0.8"
			})" ) );

		snow = create_custom_material( _( "hw_snow_material" ), _( "VertexLitGeneric" ),
			_( R"("VertexLitGeneric" {
"$basetexture"                "dev/snowfield"
                "$additive"                    "1"
                "$envmap"                    "editor/cube_vertigo"
                "$envmaptint"                "[0 0.5 0.55]"
                "$envmapfresnel"            "1"
                "$envmapfresnelminmaxexp"   "[0.00005 0.6 6]"
                "$alpha"                    "1"
 
                Proxies
                {
                    TextureScroll
                    {
                        "texturescrollvar"            "$baseTextureTransform"
                        "texturescrollrate"            "0.10"
                        "texturescrollangle"        "270"
                    }
                }
			})" ) );

		textured->increment_reference_count( );
		flat->increment_reference_count( );
		glow->increment_reference_count( );
		snow->increment_reference_count( );
	}

	c_base_entity* local = i::client_entity_list->get_entity_from_index< c_base_entity>( i::engine_client->get_local_player_index( ) );
	if ( !local )
	{
		original( ecx, edx, ctx, state, info, matrix );
		return;
	}

	auto other_chams = [ & ]( )
	{
		if ( strstr( info->m_model->m_name + 17, "arms" ) )
		{
			c_material* material = nullptr;
			switch ( c::get<int>( vars.chams_arm_material ) )
			{
			case 0: material = flat; break;
			case 1: material = textured; break;
			}

			c_material* overlay_material = nullptr;
			switch ( c::get<int>( vars.chams_overlay_arm_material ) )
			{
			case 0: overlay_material = glow; break;
			case 1: overlay_material = snow; break;
			}

			if ( c::get<bool>( vars.chams_arm_render_original ) )
				original( ecx, edx, ctx, state, info, matrix );

			if ( c::get<bool>( vars.chams_arm ) )
			{
				material->set_color( c::get<color>( vars.chams_arm_color ).base<color_r>( ), c::get<color>( vars.chams_arm_color ).base<color_g>( ), c::get<color>( vars.chams_arm_color ).base<color_b>( ) );
				material->set_alpha( c::get<color>( vars.chams_arm_color ).base<color_a>( ) );
				material->set_flag( e_material_flag::material_flag_ignore_z, false );
				material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_arm_wireframe ) );

				i::model_render->force_override_material( material );
				original( ecx, edx, ctx, state, info, matrix );
			}

			if ( c::get<bool>( vars.chams_arm_overlay ) )
			{
				bool found = false;
				c_material_var* material_var = overlay_material->find_var( _( "$envmaptint" ), &found );

				if ( found )
					( *( void( __thiscall** )( int, float, float, float ) )( *( DWORD* ) material_var + 44 ) )( ( uintptr_t ) material_var, c::get<color>( vars.chams_arm_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_arm_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_arm_overlay_color ).base<color_b>( ) );

				overlay_material->set_color( c::get<color>( vars.chams_arm_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_arm_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_arm_overlay_color ).base<color_b>( ) );
				overlay_material->set_alpha( c::get<color>( vars.chams_arm_overlay_color ).base<color_a>( ) );
				overlay_material->set_flag( e_material_flag::material_flag_ignore_z, false );
				overlay_material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_arm_wireframe ) );

				i::model_render->force_override_material( overlay_material );
				original( ecx, edx, ctx, state, info, matrix );
			}
		}
		else if ( strstr( info->m_model->m_name, "models/weapons/v" ) )
		{
			c_material* material = nullptr;
			switch ( c::get<int>( vars.chams_weapon_material ) )
			{
			case 0: material = flat; break;
			case 1: material = textured; break;
			}

			c_material* overlay_material = nullptr;
			switch ( c::get<int>( vars.chams_overlay_weapon_material ) )
			{
			case 0: overlay_material = glow; break;
			case 1: overlay_material = snow; break;
			}

			if ( c::get<bool>( vars.chams_weapon_render_original ) )
				original( ecx, edx, ctx, state, info, matrix );

			if ( c::get<bool>( vars.chams_weapon ) )
			{
				material->set_color( c::get<color>( vars.chams_weapon_color ).base<color_r>( ), c::get<color>( vars.chams_weapon_color ).base<color_g>( ), c::get<color>( vars.chams_weapon_color ).base<color_b>( ) );
				material->set_alpha( c::get<color>( vars.chams_weapon_color ).base<color_a>( ) );
				material->set_flag( e_material_flag::material_flag_ignore_z, false );
				material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_weapon_wireframe ) );

				i::model_render->force_override_material( material );
				original( ecx, edx, ctx, state, info, matrix );
			}

			if ( c::get<bool>( vars.chams_weapon_overlay ) )
			{
				bool found = false;
				c_material_var* material_var = overlay_material->find_var( _( "$envmaptint" ), &found );

				if ( found )
					( *( void( __thiscall** )( int, float, float, float ) )( *( DWORD* ) material_var + 44 ) )( ( uintptr_t ) material_var, c::get<color>( vars.chams_weapon_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_weapon_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_weapon_overlay_color ).base<color_b>( ) );

				overlay_material->set_color( c::get<color>( vars.chams_weapon_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_weapon_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_weapon_overlay_color ).base<color_b>( ) );
				overlay_material->set_alpha( c::get<color>( vars.chams_weapon_overlay_color ).base<color_a>( ) );
				overlay_material->set_flag( e_material_flag::material_flag_ignore_z, false );
				overlay_material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_weapon_wireframe ) );

				i::model_render->force_override_material( overlay_material );
				original( ecx, edx, ctx, state, info, matrix );
			}
		}
	};

	other_chams( );

	auto player_chams = [ & ]( )
	{
		c_base_entity* entity = i::client_entity_list->get_entity_from_index< c_base_entity>( info->m_entity_index );
		if ( entity == nullptr || !entity->is_alive( ) || !entity->is_player( ) || entity->team( ) == local->team( ) || entity->has_gun_game_immunity( ) )
		{
			original( ecx, edx, ctx, state, info, matrix );
			return;
		}

		if ( c::get<bool>( vars.chams_render_original ) )
			original( ecx, edx, ctx, state, info, matrix );

		c_material* material = nullptr;
		switch ( c::get<int>( vars.chams_material ) )
		{
		case 0: material = flat; break;
		case 1: material = textured; break;
		}

		if ( c::get<bool>( vars.chams_invisible ) )
		{
			material->set_color( c::get<color>( vars.chams_invisible_color ).base<color_r>( ), c::get<color>( vars.chams_invisible_color ).base<color_g>( ), c::get<color>( vars.chams_invisible_color ).base<color_b>( ) );
			material->set_alpha( c::get<color>( vars.chams_invisible_color ).base<color_a>( ) );
			material->set_flag( e_material_flag::material_flag_ignore_z, true );
			material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_wireframe ) );

			i::model_render->force_override_material( material );
			original( ecx, edx, ctx, state, info, matrix );

			if ( !c::get<bool>( vars.chams_visible ) )
				i::model_render->force_override_material( nullptr );
		}

		if ( c::get<bool>( vars.chams_visible ) )
		{
			material->set_color( c::get<color>( vars.chams_visible_color ).base<color_r>( ), c::get<color>( vars.chams_visible_color ).base<color_g>( ), c::get<color>( vars.chams_visible_color ).base<color_b>( ) );
			material->set_alpha( c::get<color>( vars.chams_visible_color ).base<color_a>( ) );
			material->set_flag( e_material_flag::material_flag_ignore_z, false );
			material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_wireframe ) );

			/* no need to set wireframe flag down here too, since we are already calling it up there */

			i::model_render->force_override_material( material );
			original( ecx, edx, ctx, state, info, matrix );
		}
		else
		{
			i::model_render->force_override_material( nullptr );
			original( ecx, edx, ctx, state, info, matrix );
		}

		c_material* overlay_material = nullptr;
		switch ( c::get<int>( vars.chams_overlay_material ) )
		{
		case 0: overlay_material = glow; break;
		case 1: overlay_material = snow; break;
		}

		if ( c::get<bool>( vars.chams_invisible_overlay ) )
		{
			bool found = false;
			c_material_var* material_var = overlay_material->find_var( _( "$envmaptint" ), &found );

			if ( found )
				( *( void( __thiscall** )( int, float, float, float ) )( *( DWORD* ) material_var + 44 ) )( ( uintptr_t ) material_var, c::get<color>( vars.chams_invisible_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_invisible_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_invisible_overlay_color ).base<color_b>( ) );

			overlay_material->set_color( c::get<color>( vars.chams_invisible_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_invisible_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_invisible_overlay_color ).base<color_b>( ) );
			overlay_material->set_alpha( c::get<color>( vars.chams_invisible_overlay_color ).base<color_a>( ) );
			overlay_material->set_flag( e_material_flag::material_flag_ignore_z, true );
			overlay_material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_wireframe ) );

			i::model_render->force_override_material( overlay_material );
			original( ecx, edx, ctx, state, info, matrix );
		}

		if ( c::get<bool>( vars.chams_visible_overlay ) )
		{
			bool found = false;
			c_material_var* material_var = overlay_material->find_var( _( "$envmaptint" ), &found );

			if ( found )
				( *( void( __thiscall** )( int, float, float, float ) )( *( DWORD* ) material_var + 44 ) )( ( uintptr_t ) material_var, c::get<color>( vars.chams_visible_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_visible_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_visible_overlay_color ).base<color_b>( ) );

			overlay_material->set_color( c::get<color>( vars.chams_visible_overlay_color ).base<color_r>( ), c::get<color>( vars.chams_visible_overlay_color ).base<color_g>( ), c::get<color>( vars.chams_visible_overlay_color ).base<color_b>( ) );
			overlay_material->set_alpha( c::get<color>( vars.chams_visible_overlay_color ).base<color_a>( ) );
			overlay_material->set_flag( e_material_flag::material_flag_ignore_z, false );
			overlay_material->set_flag( e_material_flag::material_flag_wireframe, c::get<bool>( vars.chams_wireframe ) );

			i::model_render->force_override_material( overlay_material );
			original( ecx, edx, ctx, state, info, matrix );
		}
	};

	player_chams( );

	SEH_END

		original( ecx, edx, ctx, state, info, matrix );
	i::model_render->force_override_material( nullptr );
}