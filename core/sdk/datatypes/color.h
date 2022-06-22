#pragma once
// used: std::array
#include <array>
#include <algorithm>
#include "../../../dependencies/imgui/imgui.h"

enum
{
	color_r = 0,
	color_g = 1,
	color_b = 2,
	color_a = 3
};

struct color_rgbexp32_t
{
	std::uint8_t r, g, b;
	char exponent;
};

class color
{
public:
	color( ) = default;

	constexpr color( std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a = 255 ) :
		arr_color( { r, g, b, a } ) { }

	constexpr color( int r, int g, int b, int a = 255 ) :
		arr_color( { static_cast< std::uint8_t >( r ), static_cast< std::uint8_t >( g ), static_cast< std::uint8_t >( b ), static_cast< std::uint8_t >( a ) } ) { }

	constexpr color( float r, float g, float b, float a = 1.0f ) :
		arr_color( { static_cast< std::uint8_t >( r * 255.f ), static_cast< std::uint8_t >( g * 255.f ), static_cast< std::uint8_t >( b * 255.f ), static_cast< std::uint8_t >( a * 255.f ) } ) { }

	void get( std::uint8_t& r, std::uint8_t& g, std::uint8_t& b, std::uint8_t& a ) const
	{
		r = arr_color[ color_r ];
		g = arr_color[ color_g ];
		b = arr_color[ color_b ];
		a = arr_color[ color_a ];
	}

	[[nodiscard]] ImU32 get_u32( const float alpha_multiplier = 1.0f ) const
	{
		return ImGui::GetColorU32( this->get_imvec4( alpha_multiplier ) );
	}

	[[nodiscard]] ImVec4 get_imvec4( const float alpha_multiplier = 1.0f ) const
	{
		return ImVec4( this->base<color_r>( ), this->base<color_g>( ), this->base<color_b>( ), this->base<color_a>( ) * alpha_multiplier );
	}

	std::uint8_t& operator[]( const std::size_t i )
	{
		return this->arr_color[ i ];
	}

	const std::uint8_t& operator[]( const std::size_t i ) const
	{
		return this->arr_color[ i ];
	}

	bool operator==( const color& color_second ) const
	{
		return this->arr_color == color_second.arr_color;
	}

	bool operator!=( const color& colSecond ) const
	{
		return !( operator==( colSecond ) );
	}

	color& operator=( const color& colFrom )
	{
		arr_color[ color_r ] = colFrom.arr_color[ color_r ];
		arr_color[ color_g ] = colFrom.arr_color[ color_g ];
		arr_color[ color_b ] = colFrom.arr_color[ color_b ];
		arr_color[ color_a ] = colFrom.arr_color[ color_a ];
		return *this;
	}

	template <std::size_t N>
	[[nodiscard]] std::uint8_t get( ) const
	{
		static_assert( N >= color_r && N <= color_a, "given index is out of range" );
		return arr_color[ N ];
	}

	template <std::size_t N>
	[[nodiscard]] float base( ) const
	{
		static_assert( N >= color_r && N <= color_a, "given index is out of range" );
		return arr_color[ N ] / 255.f;
	}

	[[nodiscard]] std::array<float, 3U> base( ) const
	{
		std::array<float, 3U> arr_base_color = { };
		arr_base_color[ color_r ] = this->base<color_r>( );
		arr_base_color[ color_g ] = this->base<color_g>( );
		arr_base_color[ color_b ] = this->base<color_b>( );
		return arr_base_color;
	}

	static color from_base_3( float arr_base[ 3 ] )
	{
		return color( arr_base[ 0 ], arr_base[ 1 ], arr_base[ 2 ] );
	}

	[[nodiscard]] std::array<float, 4U> base_alpha( ) const
	{
		std::array<float, 4U> arr_base_color = { };
		arr_base_color[ color_r ] = this->base<color_r>( );
		arr_base_color[ color_g ] = this->base<color_g>( );
		arr_base_color[ color_b ] = this->base<color_b>( );
		arr_base_color[ color_a ] = this->base<color_a>( );
		return arr_base_color;
	}

	static color from_base_4( float arr_base[ 4 ] )
	{
		return color( arr_base[ 0 ], arr_base[ 1 ], arr_base[ 2 ], arr_base[ 3 ] );
	}

	static color blend( const color& first_color, const color& second_color, const float alpha_multiplier )
	{
		return color
		(
			first_color.base<color_r>( ) + std::clamp( alpha_multiplier, 0.f, 1.f ) * ( second_color.base<color_r>( ) - first_color.base<color_r>( ) ),
			first_color.base<color_g>( ) + std::clamp( alpha_multiplier, 0.f, 1.f ) * ( second_color.base<color_g>( ) - first_color.base<color_g>( ) ),
			first_color.base<color_b>( ) + std::clamp( alpha_multiplier, 0.f, 1.f ) * ( second_color.base<color_b>( ) - first_color.base<color_b>( ) ),
			first_color.base<color_a>( ) + std::clamp( alpha_multiplier, 0.f, 1.f ) * ( second_color.base<color_a>( ) - first_color.base<color_a>( ) )
		);
	}
private:
	std::array<std::uint8_t, 4U> arr_color;
};
