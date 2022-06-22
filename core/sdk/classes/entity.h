#pragma once
#include <functional>

#include "../../sdk/datatypes/c_usercmd.h"
#include "../../../utilities/math/vector.h"
#include "../../props/props.h"

enum e_data_update_type : int
{
	data_update_created = 0,
	data_update_datatable_changed,
};

enum e_precipitation_type : int
{
	precipitation_type_rain = 0,
	precipitation_type_snow,
	precipitation_type_ash,
	precipitation_type_snowfall,
	precipitation_type_particlerain,
	precipitation_type_particleash,
	precipitation_type_particlerainstorm,
	precipitation_type_particlesnow,
	num_precipitation_types
};

enum e_team_id : int
{
	team_unassigned = 0,
	team_spectator,
	team_tt,
	team_ct
};

enum e_think_methods : int
{
	think_fire_all_functions = 0,
	think_fire_base_only,
	think_fire_all_but_base,
};

enum e_item_definition_index : short
{
	weapon_none = 0,
	weapon_deagle = 1,
	weapon_elite = 2,
	weapon_fiveseven = 3,
	weapon_glock = 4,
	weapon_ak47 = 7,
	weapon_aug = 8,
	weapon_awp = 9,
	weapon_famas = 10,
	weapon_g3sg1 = 11,
	weapon_galilar = 13,
	weapon_m249 = 14,
	weapon_m4a1 = 16,
	weapon_mac10 = 17,
	weapon_p90 = 19,
	weapon_zone_repulsor = 20,
	weapon_mp5sd = 23,
	weapon_ump45 = 24,
	weapon_xm1014 = 25,
	weapon_bizon = 26,
	weapon_mag7 = 27,
	weapon_negev = 28,
	weapon_sawedoff = 29,
	weapon_tec9 = 30,
	weapon_taser = 31,
	weapon_hkp2000 = 32,
	weapon_mp7 = 33,
	weapon_mp9 = 34,
	weapon_nova = 35,
	weapon_p250 = 36,
	weapon_shield = 37,
	weapon_scar20 = 38,
	weapon_sg556 = 39,
	weapon_ssg08 = 40,
	weapon_knife_gg = 41,
	weapon_knife = 42,
	weapon_flashbang = 43,
	weapon_hegrenade = 44,
	weapon_smokegrenade = 45,
	weapon_molotov = 46,
	weapon_decoy = 47,
	weapon_incgrenade = 48,
	weapon_c4 = 49,
	weapon_healthshot = 57,
	weapon_knife_t = 59,
	weapon_m4a1_silencer = 60,
	weapon_usp_silencer = 61,
	weapon_cz75a = 63,
	weapon_revolver = 64,
	weapon_tagrenade = 68,
	weapon_fists = 69,
	weapon_breachcharge = 70,
	weapon_tablet = 72,
	weapon_melee = 74,
	weapon_axe = 75,
	weapon_hammer = 76,
	weapon_spanner = 78,
	weapon_knife_ghost = 80,
	weapon_firebomb = 81,
	weapon_diversion = 82,
	weapon_frag_grenade = 83,
	weapon_snowball = 84,
	weapon_bumpmine = 85,
	weapon_knife_bayonet = 500,
	weapon_knife_css = 503,
	weapon_knife_flip = 505,
	weapon_knife_gut = 506,
	weapon_knife_karambit = 507,
	weapon_knife_m9_bayonet = 508,
	weapon_knife_tactical = 509,
	weapon_knife_falchion = 512,
	weapon_knife_survival_bowie = 514,
	weapon_knife_butterfly = 515,
	weapon_knife_push = 516,
	weapon_knife_cord = 517,
	weapon_knife_canis = 518,
	weapon_knife_ursus = 519,
	weapon_knife_gypsy_jackknife = 520,
	weapon_knife_outdoor = 521,
	weapon_knife_stiletto = 522,
	weapon_knife_widowmaker = 523,
	weapon_knife_skeleton = 525,
	glove_studded_brokenfang = 4725,
	glove_studded_bloodhound = 5027,
	glove_t = 5028,
	glove_ct = 5029,
	glove_sporty = 5030,
	glove_slick = 5031,
	glove_leather_handwraps = 5032,
	glove_motorcycle = 5033,
	glove_specialist = 5034,
	glove_studded_hydra = 5035,
	special_agent_blueberries_buckshot = 4619,
	special_agent_two_times_mccoy_tacp = 4680,
	special_agent_commandor_mae_jamison = 4711,
	special_agent_1st_lieutenant_farlow,
	special_agent_john_kask,
	special_agent_bio_haz_specialist,
	special_agent_sergeant_bombson,
	special_agent_chem_haz_specialist,
	special_agent_rezan_the_redshirt = 4718,
	special_agent_sir_bloody_miami_darryl = 4726,
	special_agent_safecracker_voltzmann,
	special_agent_little_kev,
	special_agent_getaway_sally = 4730,
	special_agent_number_k = 4732,
	special_agent_sir_bloody_silent_darryl = 4733,
	special_agent_sir_bloody_skullhead_darryl,
	special_agent_sir_bloody_darryl_royale,
	special_agent_sir_bloody_loudmouth_darryl,
	special_agent_t = 5036,
	special_agent_ct = 5037,
	special_agent_ground_rebel = 5105,
	special_agent_osiris,
	special_agent_shahmat,
	special_agent_muhlik,
	special_agent_soldier = 5205,
	special_agent_enforcer,
	special_agent_slingshot,
	special_agent_street_soldier,
	special_agent_operator = 5305,
	special_agent_markus_delrow,
	special_agent_michael_syfers,
	special_agent_ava,
	special_agent_3rd_commando_company = 5400,
	special_agent_seal_team_6_soldier,
	special_agent_buckshot,
	special_agent_two_times_mccoy_usaf,
	special_agent_ricksaw,
	special_agent_dragomir = 5500,
	special_agent_maximus,
	special_agent_rezan_the_ready,
	special_agent_blackwolf = 5503,
	special_agent_the_doctor,
	special_agent_dragomir_footsoldiers,
	special_agent_b_squadron_officer = 5601
};

enum e_team : int {
	none = 0,
	spectators,
	tt,
	ct
};

enum e_weapon_type : int
{
	weapontype_knife = 0,
	weapontype_pistol = 1,
	weapontype_submachinegun = 2,
	weapontype_rifle = 3,
	weapontype_shotgun = 4,
	weapontype_sniper = 5,
	weapontype_machinegun = 6,
	weapontype_c4 = 7,
	weapontype_placeholder = 8,
	weapontype_grenade = 9,
	weapontype_healthshot = 11,
	weapontype_fists = 12,
	weapontype_breachcharge = 13,
	weapontype_bumpmine = 14,
	weapontype_tablet = 15,
	weapontype_melee = 16
};

enum e_solid_type : int
{
	solid_none = 0,
	solid_bsp,
	solid_bbox,
	solid_obb,
	solid_obb_yaw,
	solid_custom,
	solid_vphysics,
	solid_last
};

enum e_player_filters
{
	dead = 1 << 0,
	dormant = 1 << 1,
	immune = 1 << 2,
	teammates = 1 << 3,
	enemies = 1 << 4,
	self = 1 << 5,
};

class c_renderable
{
public:
	math::vec3& render_origin( )
	{
		return mem::call_vfunc<math::vec3&>( this, 1 );
	}
};

class c_base_entity
{
public:
	void* networkable( )
	{
		return reinterpret_cast< void* >( std::uint32_t( this ) + 0x8 );
	}

	int index( )
	{
		return mem::call_vfunc< int >( networkable( ), 10 );
	}

	bool dormant( )
	{
		return mem::call_vfunc< bool >( networkable( ), 9 );
	}

	/* CBasePlayer */
	add_pvariable( float, fall_velocity, "CBasePlayer->m_flFallVelocity" );

	add_variable( int, health, "CBasePlayer->m_iHealth" );
	add_variable( int, tick_base, "CBasePlayer->m_nTickBase" );
	add_variable( int, flags, "CBasePlayer->m_fFlags" );
	add_pvariable( int, observer_mode, "CBasePlayer->m_iObserverMode" );
	add_variable( int, observer_target, "CBasePlayer->m_hObserverTarget" );
	add_variable_offset( int, button_disabled, "CBasePlayer->m_hViewEntity", -0xC );
	add_variable_offset( int, button_forced, "CBasePlayer->m_hViewEntity", -0x8 );
	add_pvariable_offset( c_usercmd*, current_command, "CBasePlayer->m_hViewEntity", -0x4 );

	add_variable( math::vec3, velocity, "CBasePlayer->m_vecVelocity[0]" );
	add_variable( math::vec3, view_punch_angle, "CBasePlayer->m_viewPunchAngle" );
	add_variable( math::vec3, aim_punch_angle, "CBasePlayer->m_aimPunchAngle" );
	add_variable( math::vec3, view_offset, "CBasePlayer->m_vecViewOffset[0]" );

	/* CCSPlayer */
	add_variable( bool, has_gun_game_immunity, "CCSPlayer->m_bGunGameImmunity" );

	/* CBaseEntity */
	add_variable( int, team, "CBaseEntity->m_iTeamNum" );

	bool is_alive( )
	{
		if ( !this )
			return false;

		return this->health( ) > 0;
	}

	bool is_player( )
	{
		return mem::call_vfunc<bool>( this, 158 );
	}
};