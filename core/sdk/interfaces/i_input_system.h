#pragma once
#include "../../../utilities/memory/memory.h"

enum e_button_code : int
{
	button_code_invalid = -1,
	button_code_none = 0,

	key_first = 0,
	key_none = key_first,

	/* keys */
	key_0,
	key_1,
	key_2,
	key_3,
	key_4,
	key_5,
	key_6,
	key_7,
	key_8,
	key_9,
	key_a,
	key_b,
	key_c,
	key_d,
	key_e,
	key_f,
	key_g,
	key_h,
	key_i,
	key_j,
	key_k,
	key_l,
	key_m,
	key_n,
	key_o,
	key_p,
	key_q,
	key_r,
	key_s,
	key_t,
	key_u,
	key_v,
	key_w,
	key_x,
	key_y,
	key_z,
	key_pad_0,
	key_pad_1,
	key_pad_2,
	key_pad_3,
	key_pad_4,
	key_pad_5,
	key_pad_6,
	key_pad_7,
	key_pad_8,
	key_pad_9,
	key_pad_divide,
	key_pad_multiply,
	key_pad_minus,
	key_pad_plus,
	key_pad_enter,
	key_pad_decimal,
	key_lbracket,
	key_rbracket,
	key_semicolon,
	key_apostrophe,
	key_backquote,
	key_comma,
	key_period,
	key_slash,
	key_backslash,
	key_minus,
	key_equal,
	key_enter,
	key_space,
	key_backspace,
	key_tab,
	key_capslock,
	key_numlock,
	key_escape,
	key_scrolllock,
	key_insert,
	key_delete,
	key_home,
	key_end,
	key_pageup,
	key_pagedown,
	key_break,
	key_lshift,
	key_rshift,
	key_lalt,
	key_ralt,
	key_lcontrol,
	key_rcontrol,
	key_lwin,
	key_rwin,
	key_app,
	key_up,
	key_left,
	key_down,
	key_right,
	key_f1,
	key_f2,
	key_f3,
	key_f4,
	key_f5,
	key_f6,
	key_f7,
	key_f8,
	key_f9,
	key_f10,
	key_f11,
	key_f12,
	key_capslocktoggle,
	key_numlocktoggle,
	key_scrolllocktoggle,

	key_last = key_scrolllocktoggle,
	key_count = key_last - key_first + 1,

	/* mouse */
	mouse_first = key_last + 1,

	mouse_left = mouse_first,
	mouse_right,
	mouse_middle,
	mouse_4,
	mouse_5,
	mouse_wheel_up,		// a fake button which is 'pressed' and 'released' when the wheel is moved up 
	mouse_wheel_down,	// a fake button which is 'pressed' and 'released' when the wheel is moved down

	mouse_last = mouse_wheel_down,
	mouse_count = mouse_last - mouse_first + 1,
};

enum e_mouse_code_state : int
{
	button_released = 0,
	button_pressed,
	button_doubleclicked,
};

class i_input_system
{
public:
	void enable_input( bool enable_input )
	{
		mem::call_vfunc<void>( this, 11, enable_input );
	}

	bool is_button_down( e_button_code button_code )
	{
		return mem::call_vfunc<bool>( this, 15, button_code );
	}

	e_button_code virtual_key_to_button_code( int virtual_key )
	{
		return mem::call_vfunc<e_button_code>( this, 45, virtual_key );
	}
};