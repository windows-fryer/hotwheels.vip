#include "key_handler.h"

enum e_mouse_button : int
{
	mouse_left = 0,
	mouse_right,
	mouse_middle,
	mouse_side1,
	mouse_side2,
};

bool is_mouse_clicked( int key, bool repeat )
{
	return ImGui::IsMouseClicked( key, repeat );
}

bool is_mouse_double_clicked( int key )
{
	return ImGui::IsMouseDoubleClicked( key );
}

bool is_mouse_down( int key )
{
	return ImGui::IsMouseDown( key );
}

bool is_mouse_released( int key )
{
	return ImGui::IsMouseReleased( key );
}

bool is_key_pressed( int key, bool repeat )
{
	if ( key > 0x06 )
		return ImGui::IsKeyPressed( key, repeat );

	switch ( key ) {
	case VK_LBUTTON:
		return is_mouse_clicked( mouse_left, repeat );
	case VK_MBUTTON:
		return is_mouse_clicked( mouse_middle, repeat );
	case VK_RBUTTON:
		return is_mouse_clicked( mouse_right, repeat );
	case VK_XBUTTON1:
		return is_mouse_clicked( mouse_side1, repeat );
	case VK_XBUTTON2:
		return is_mouse_clicked( mouse_side2, repeat );
	}

	return false;
}

bool is_key_down( int key )
{
	if ( key > 0x06 )
		return ImGui::IsKeyDown( key );

	switch ( key ) {
	case VK_LBUTTON:
		return is_mouse_down( mouse_left );
	case VK_MBUTTON:
		return is_mouse_down( mouse_middle );
	case VK_RBUTTON:
		return is_mouse_down( mouse_right );
	case VK_XBUTTON1:
		return is_mouse_down( mouse_side1 );
	case VK_XBUTTON2:
		return is_mouse_down( mouse_side2 );
	}

	return false;
}

bool is_key_released( int key )
{
	if ( key > 0x06 )
		return ImGui::IsKeyReleased( key );

	switch ( key ) {
	case VK_LBUTTON:
		return is_mouse_released( mouse_left );
	case VK_MBUTTON:
		return is_mouse_released( mouse_middle );
	case VK_RBUTTON:
		return is_mouse_released( mouse_right );
	case VK_XBUTTON1:
		return is_mouse_released( mouse_side1 );
	case VK_XBUTTON2:
		return is_mouse_released( mouse_side2 );
	}

	return false;
}

bool c_key_handler::auto_check( int key, int style )
{
	switch ( style )
	{
	case 0:
		return true;
	case 1:
		return LOWORD( is_key_down( key ) );
	case 2:
	{
		static bool should_return_true = false;

		if ( is_key_pressed( key, false ) )
			should_return_true = !should_return_true;

		return should_return_true ? true : false;
	}
	default:
		return true;
	}
}