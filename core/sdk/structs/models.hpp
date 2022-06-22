#pragma once
#include "../../../utilities/math/matrix.h"

struct model_t
{
	void* m_handle;
	char m_name[ 255 ];
};

struct model_render_info_t
{
	math::vec3 m_origin;
	math::vec3 m_angles;
	char pad[ 0x4 ];
	void* m_renderable;
	const model_t* m_model;
	const math::c_matrix3x4* m_model_to_world;
	const math::c_matrix3x4* m_lighting_offset;
	const math::vec3* m_lighting_origin;
	int m_flags;
	int m_entity_index;
	int m_skin;
	int m_body;
	int m_hitboxset;
	unsigned short m_instance;
};