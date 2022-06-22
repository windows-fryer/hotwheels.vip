#pragma once

#include <cstdint>

#include "../../../utilities/math/matrix.h"
#include "../../../utilities/math/vector.h"

using quaternion_t = typename float[ 4 ];

enum e_hitbox {
    hitbox_head,
    hitbox_neck,
    hitbox_pelvis,
    hitbox_stomach,
    hitbox_thorax,
    hitbox_lower_chest,
    hitbox_upper_chest,
    hitbox_right_thigh,
    hitbox_left_thigh,
    hitbox_right_calf,
    hitbox_left_calf,
    hitbox_right_foot,
    hitbox_left_foot,
    hitbox_right_hand,
    hitbox_left_hand,
    hitbox_right_upperarm,
    hitbox_right_forearm,
    hitbox_left_upperarm,
    hitbox_left_forearm,
};

enum e_hit_group {
    hit_group_invalid = -1,
    hit_group_generic,
    hit_group_head,
    hit_group_chest,
    hit_group_stomach,
    hit_group_left_arm,
    hit_group_right_arm,
    hit_group_left_leg,
    hit_group_right_leg,
    hit_group_gear = 10
};

struct studio_bone_t {
    int m_name_index;
    int m_parent;
    int m_bone_controller[ 6 ];

    math::vec3 m_position;
    quaternion_t m_quaternion;
    math::vec3 m_rotation;
    math::vec3 m_position_scale;
    math::vec3 m_rotation_scale;

    math::c_matrix3x4 m_pose_to_bone;
    quaternion_t m_quaternion_alignement;

    int m_flags;
    int m_proc_type;
    int m_proc_index;
    int m_physics_bone;
    int m_surface_prop_idx;
    int m_contents;
    int m_surf_prop_lookup;
    int m_unused[ 7 ];
};

struct studio_box_t {
    int m_bone;
    int m_group;
    math::vec3 m_mins;
    math::vec3 m_maxs;
    int m_name_index;
    int pad01[ 3 ];
    float m_radius;
    int pad02[ 4 ];
};

struct studio_hitbox_set_t {
    int m_name_index;
    int m_hitbox_count;
    int m_hitbox_index;

    inline studio_box_t* get_hitbox( int index ) const 
    {
        return ( studio_box_t* ) ( ( uintptr_t ) this + m_hitbox_index ) + index;
    }
};

struct studio_hdr_t {
    int m_id;
    int m_version;
    long m_checksum;
    char m_name_char_array[ 64 ];
    int m_length;
    math::vec3 m_eye_position;
    math::vec3 m_illium_position;
    math::vec3 m_hull_mins;
    math::vec3 m_hull_maxs;
    math::vec3 m_mins;
    math::vec3 m_maxs;
    int m_flags;
    int m_bones_count;
    int m_bone_index;
    int m_bone_controllers_count;
    int m_bone_controller_index;
    int m_hitbox_sets_count;
    int m_hitbox_set_index;
    int m_local_anim_count;
    int m_local_anim_index;
    int m_local_seq_count;
    int m_local_seq_index;
    int m_activity_list_version;
    int m_events_indexed;
    int m_textures_count;
    int m_texture_index;

    inline studio_hitbox_set_t* get_hitbox_set( int index ) const 
    {
        if ( index > m_hitbox_sets_count )
            return nullptr;

        return ( studio_hitbox_set_t* ) ( ( uintptr_t ) this + m_hitbox_set_index ) + index;
    }

    inline studio_box_t* get_hitbox( int index, int set_index ) const
    {
        const auto set = get_hitbox_set( set_index );

        if ( !set )
            return nullptr;

        return set->get_hitbox( index );
    }

    inline studio_bone_t* get_bone( int index ) const 
    {
        if ( index > m_bones_count )
            return nullptr;

        return ( studio_bone_t* ) ( ( uintptr_t ) this + m_bone_index ) + index;
    }
};