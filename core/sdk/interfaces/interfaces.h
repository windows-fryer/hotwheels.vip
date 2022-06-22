#pragma once
#include <string_view>
#include <d3d9.h>

#include "i_input.h"
#include "i_surface.h"
#include "i_input_system.h"
#include "i_model_render.h"
#include "i_engine_client.h"
#include "i_base_client_dll.h"
#include "i_material_system.h"
#include "i_global_vars_base.h"
#include "i_key_values_system.h"
#include "i_client_mode_shared.h"
#include "i_client_entity_list.h"

class c_interface_register
{
public:
	instantiate_interface_fn m_create_fn;
	const char* m_name;			
	c_interface_register* m_next;
};

namespace i
{
	bool init( );

	template <typename T>
	T* capture( const std::string_view module_name, const std::string_view interface_name );

	inline i_base_client_dll* client = nullptr;
	inline i_client_mode_shared* client_mode = nullptr;
	inline i_client_state* client_state = nullptr;
	inline i_surface* surface = nullptr;
	inline i_input* input = nullptr;
	inline i_input_system* input_system = nullptr;
	inline i_client_entity_list* client_entity_list = nullptr;
	inline i_model_render* model_render = nullptr;
	inline i_material_system* material_system = nullptr;
	inline i_engine_client* engine_client = nullptr;
	inline i_key_values_system* key_values_system = nullptr;
	inline i_global_vars_base* globals = nullptr;
	inline IDirect3DDevice9* direct_device = nullptr;

	inline void* file_system = nullptr;
}