#pragma once
#include <d3d9.h>

#include "detour_hook.h"
#include "../sdk/structs/models.hpp"
#include "../../utilities/math/matrix.h"

class i_surface;
class c_usercmd;
class i_base_client_dll;

enum e_client_frame_stage;

namespace h
{
	void* __fastcall alloc_key_values_memory( void* thisptr, int edx, int size );
	void __fastcall create_move_proxy( i_base_client_dll* thisptr, int edx, int sequence_number, float input_sample_frametime, bool is_active );
	void __fastcall frame_stage_notify( i_base_client_dll* thisptr, int edx, e_client_frame_stage stage );
	void __fastcall	draw_print_text( int ecx, int edx, const wchar_t* text, int text_length, int draw_type );
	void __fastcall	draw_model_execute( int ecx, int edx, void* ctx, void* state, model_render_info_t* info, math::c_matrix3x4* matrix );
	int	__cdecl	vsnprintf( char* text, int text_length, const char* fmt, ... );
	void __fastcall push_notice( int ecx, int edx, const char* text, int text_length, const char* always_null );
	void __fastcall	lock_cursor( i_surface* thisptr, int edx );
	LONG __stdcall end_scene( IDirect3DDevice9* device );
	long __stdcall reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presenation_parameters );

	long __stdcall wnd_proc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );

	bool init( );
	void revert( );
}

namespace detours
{
	inline c_detour_hook alloc_key_values_memory;
	inline c_detour_hook create_move_proxy;
	inline c_detour_hook frame_stage_notify;
	inline c_detour_hook draw_print_text;
	inline c_detour_hook draw_model_execute;
	inline c_detour_hook vsnprintf;
	inline c_detour_hook push_notice;
	inline c_detour_hook lock_cursor;
	inline c_detour_hook end_scene;
	inline c_detour_hook reset;
}