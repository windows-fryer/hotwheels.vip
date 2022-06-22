#pragma once
#include <cstddef>

enum e_field_types : int
{
	field_void = 0,			// no type or value
	field_float,			// any floating point value
	field_string,			// a string id (return from alloc_string)
	field_vector,			// any vector, qangle, or angularimpulse
	field_quaternion,		// a quaternion
	field_integer,			// any integer or enum
	field_boolean,			// boolean, implemented as an int, i may use this as a hint for compression
	field_short,			// 2 byte integer
	field_character,		// a byte
	field_color32,			// 8-bit per channel r,g,b,a (32bit color)
	field_embedded,			// an embedded object with a datadesc, recursively traverse and embedded class/structure based on an additional typedescription
	field_custom,			// special type that contains function pointers to it's read/write/parse functions
	field_classptr,			// cbaseentity*
	field_ehandle,			// entity handle
	field_edict,			// edict_t*
	field_position_vector,	// a world coordinate (these are fixed up across level transitions automagically)
	field_time,				// a floating point time (these are fixed up automatically too!)
	field_tick,				// an integer tick count( fixed up similarly to time)
	field_modelname,		// engine string that is a model name (needs precache)
	field_soundname,		// engine string that is a sound name (needs precache)
	field_input,			// a list of inputed data fields (all derived from cmultiinputvar)
	field_function,			// a class function pointer (think, use, etc)
	field_vmatrix,			// a vmatrix (output coords are not worldspace)
	field_vmatrix_worldspace,// a vmatrix that maps some local space to world space (translation is fixed up on level transitions)
	field_matrix3x4_worldspace,	// matrix3x4_t that maps some local space to world space (translation is fixed up on level transitions)
	field_interval,			// a start and range floating point interval ( e.g., 3.2->3.6 == 3.2 and 0.4 )
	field_modelindex,		// a model index
	field_materialindex,	// a material index (using the material precache string table)
	field_vector2d,			// 2 floats
	field_integer64,		// 64bit integer
	field_vector4d,			// 4 floats
	field_typecount
};

enum
{
	td_offset_normal = 0,
	td_offset_packed = 1,
	td_offset_count
};

struct data_map_t;
struct type_description_t
{
public:
	e_field_types			m_field_type;						//0x0000
	const char* m_field_name;					//0x0004
	int					m_field_offset[ td_offset_count ];	//0x0008
	unsigned short		m_field_size;						//0x0010
	short				m_flags;							//0x0012
	std::byte			pad0[ 0xC ];						//0x0014
	data_map_t* m_type_description;				//0x0020
	std::byte			pad1[ 0x18 ];						//0x0024
}; // size: 0x003C

struct data_map_t
{
	type_description_t* m_data_desc;
	int					m_data_fields;
	const char* m_data_class_name;
	data_map_t* m_base_map;
	bool				m_chains_validated;
	bool				m_packed_offsets_computed;
	int					m_packed_size;
};
