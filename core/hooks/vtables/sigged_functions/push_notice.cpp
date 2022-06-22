#include "../../hooks.h"
#include "../../../cfg/config.h"
#include "../../../../utilities/encryption/xorstr.h"

auto rgb_to_hex = [ & ]( int r, int g, int b, bool with_hash = false )
{
	std::stringstream ss;
	if ( with_hash )
		ss << "#";

	ss << std::hex << ( r << 16 | g << 8 | b );
	return ss.str( );
};

void __fastcall h::push_notice( int ecx, int edx, const char* text, int text_length, const char* always_null )
{
	static auto original = detours::push_notice.get_original<decltype( &h::push_notice )>( );

	std::string config_saved_text = std::string( "<font color=\"" ).append( rgb_to_hex( c::get<color>( vars.color_log_prefix ).base<color_r>( ) * 255, c::get<color>( vars.color_log_prefix ).base<color_g>( ) * 255, c::get<color>( vars.color_log_prefix ).base<color_b>( ) * 255, true ) ).append( "\">hotwheels | </font><font color=\"" ).append( rgb_to_hex( c::get<color>( vars.color_log_config_print ).base<color_r>( ) * 255, c::get<color>( vars.color_log_config_print ).base<color_g>( ) * 255, c::get<color>( vars.color_log_config_print ).base<color_b>( ) * 255, true ).c_str( ) ).append( std::vformat( _( "\">saved configuration {}</font>" ), std::make_format_args( c::saved_config_file_name ) ) );
	std::string config_loaded_text = std::string( "<font color=\"" ).append( rgb_to_hex( c::get<color>( vars.color_log_prefix ).base<color_r>( ) * 255, c::get<color>( vars.color_log_prefix ).base<color_g>( ) * 255, c::get<color>( vars.color_log_prefix ).base<color_b>( ) * 255, true ) ).append( "\">hotwheels | </font><font color=\"" ).append( rgb_to_hex( c::get<color>( vars.color_log_config_print ).base<color_r>( ) * 255, c::get<color>( vars.color_log_config_print ).base<color_g>( ) * 255, c::get<color>( vars.color_log_config_print ).base<color_b>( ) * 255, true ).c_str( ) ).append( std::vformat( _( "\">loaded configuration {}</font>" ), std::make_format_args( c::loaded_config_file_name ) ) );

	switch ( fnv1a::hash( text ) )
	{
	case fnv1a::hash_const( "##loaded config" ):
	{
		return original( ecx, edx, config_loaded_text.c_str( ), config_loaded_text.size( ), config_loaded_text.c_str( ) );
		break;
	}
	case fnv1a::hash_const( "##saved config" ):
	{
		return original( ecx, edx, config_saved_text.c_str( ), config_saved_text.size( ), config_saved_text.c_str( ) );
		break;
	}
	}

	return original( ecx, edx, text, text_length, always_null );
}