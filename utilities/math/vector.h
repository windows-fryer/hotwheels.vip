#pragma once
#include <array>
#include <algorithm>
#include <cmath>
#include <corecrt_math.h>
#include <type_traits>
#include <xtr1common>

namespace math
{
	template< class T = float >
	class vec2
	{
	public:
		T x { }, y { };
		constexpr vec2( const T _X = 0, const T _Y = 0 ) : x { _X }, y { _Y } { };

		bool valid( ) const
		{
			return std::isfinite< T >( x ) && std::isfinite< T >( y );
		};
		
		vec2 operator-( const vec2& sub ) const
		{
			return vec2( x - sub.x, y - sub.y );
		}
		vec2 operator-( const int& sub ) const
		{
			return vec2( x - sub, y - sub );
		}
		vec2 operator+( const vec2& add ) const
		{
			return vec2( x + add.x, y + add.y );
		}
		vec2 operator+( const int& add ) const
		{
			return vec2( x + add, y + add );
		}
		constexpr vec2& operator-=( const vec2& sub )
		{
			x -= sub.x;
			y -= sub.y;
			return *this;
		}
		constexpr vec2& operator+=( const vec2& add )
		{
			x += add.x;
			y += add.y;
			return *this;
		}
	};

	class vec3
	{
	public:
		float x { }, y { }, z { };

		constexpr vec3( float _x = 0, float _y = 0, float _z = 0 ) : x( _x ), y( _y ), z( _z ) { };

		constexpr vec3( float* _fp ) : x( _fp[ 0 ] ), y( _fp[ 1 ] ), z( _fp[ 2 ] ) { };

		bool valid( ) const
		{
			return std::isfinite( this->x ) && std::isfinite( this->y ) && std::isfinite( this->z );
		}

		constexpr void invalidate( )
		{
			this->x = this->y = this->z = std::numeric_limits< float >::infinity( );
		};

		[[nodiscard]] float* data( )
		{
			return reinterpret_cast< float* >( this );
		}

		bool is_equal( const vec3& to_this, const float error_margin = std::numeric_limits< float >::epsilon( ) ) const
		{
			return ( std::fabsf( this->x - to_this.x ) < error_margin && std::fabsf( this->y - to_this.y ) < error_margin &&
				std::fabsf( this->z - to_this.z ) < error_margin );
		}

		bool is_zero( ) const
		{
			return ( std::fpclassify( this->x ) == FP_ZERO && std::fpclassify( this->y ) == FP_ZERO && std::fpclassify( this->z ) == FP_ZERO );
		}

		[[nodiscard]] constexpr float dot_product( const vec3& dot ) const
		{
			return ( this->x * dot.x + this->y * dot.y + this->z * dot.z );
		}

		[[nodiscard]] constexpr float length_sqr( ) const
		{
			return dot_product( *this );
		}

		[[nodiscard]] float length( ) const
		{
			return std::sqrtf( this->length_sqr( ) );
		}

		[[nodiscard]] constexpr float length_2d_sqr( ) const
		{
			return ( this->x * this->x + this->y * this->y );
		}

		[[nodiscard]] float length_2d( ) const
		{
			return std::sqrtf( this->length_2d_sqr( ) );
		}

		[[nodiscard]] float dist_to( const vec3& end ) const
		{
			return ( *this - end ).length( );
		}

		[[nodiscard]] constexpr float dist_to_sqr( const vec3& end ) const
		{
			return ( *this - end ).length_sqr( );
		}

		float normalize_in_place( )
		{
			const float length = this->length( ), radius = 1.0f / ( length + std::numeric_limits< float >::epsilon( ) );

			this->x *= radius;
			this->y *= radius;
			this->z *= radius;

			return length;
		}

		vec3 clamp( )
		{
			this->x = std::clamp( this->x, -89.f, 89.f );
			this->y = std::clamp( this->y, -180.f, 180.f );
			this->z = std::clamp( this->z, -50.f, 50.f );
			return *this;
		}

		vec3 normalize( )
		{
			this->x = std::isfinite( this->x ) ? std::remainderf( this->x, 360.f ) : 0.f;
			this->y = std::isfinite( this->y ) ? std::remainderf( this->y, 360.f ) : 0.f;
			this->z = std::clamp( this->z, -50.f, 50.f );
			return *this;
		}

		constexpr vec3 cross_product( const vec3& cross ) const
		{
			return vec3( this->y * cross.z - this->z * cross.y, this->z * cross.x - this->x * cross.z, this->x * cross.y - this->y * cross.x );
		}

		float& operator[]( const std::size_t i )
		{
			return this->data( )[ i ];
		}

		bool operator==( const vec3& base ) const
		{
			return this->is_equal( base );
		}

		bool operator!=( const vec3& base ) const
		{
			return !this->is_equal( base );
		}

		constexpr vec3& operator=( const vec3& base )
		{
			this->x = base.x;
			this->y = base.y;
			this->z = base.z;
			return *this;
		}

		constexpr vec3& operator+=( const vec3& base )
		{
			this->x += base.x;
			this->y += base.y;
			this->z += base.z;
			return *this;
		}

		constexpr vec3& operator-=( const vec3& base )
		{
			this->x -= base.x;
			this->y -= base.y;
			this->z -= base.z;
			return *this;
		}

		constexpr vec3& operator*=( const vec3& base )
		{
			this->x *= base.x;
			this->y *= base.y;
			this->z *= base.z;
			return *this;
		}

		constexpr vec3& operator/=( const vec3& base )
		{
			this->x /= base.x;
			this->y /= base.y;
			this->z /= base.z;
			return *this;
		}

		constexpr vec3& operator+=( const float add )
		{
			this->x += add;
			this->y += add;
			this->z += add;
			return *this;
		}

		constexpr vec3& operator-=( const float sub )
		{
			this->x -= sub;
			this->y -= sub;
			this->z -= sub;
			return *this;
		}

		constexpr vec3& operator*=( const float mult )
		{
			this->x *= mult;
			this->y *= mult;
			this->z *= mult;
			return *this;
		}

		constexpr vec3& operator/=( const float div )
		{
			this->x /= div;
			this->y /= div;
			this->z /= div;
			return *this;
		}

		vec3 operator+( const vec3& add ) const
		{
			return vec3( this->x + add.x, this->y + add.y, this->z + add.z );
		}

		vec3 operator-( const vec3& sub ) const
		{
			return vec3( this->x - sub.x, this->y - sub.y, this->z - sub.z );
		}

		vec3 operator*( const vec3& mult ) const
		{
			return vec3( this->x * mult.x, this->y * mult.y, this->z * mult.z );
		}

		vec3 operator/( const vec3& div ) const
		{
			return vec3( this->x / div.x, this->y / div.y, this->z / div.z );
		}

		vec3 operator+( const float add ) const
		{
			return vec3( this->x + add, this->y + add, this->z + add );
		}

		vec3 operator-( const float sub ) const
		{
			return vec3( this->x - sub, this->y - sub, this->z - sub );
		}

		vec3 operator*( const float mult ) const
		{
			return vec3( this->x * mult, this->y * mult, this->z * mult );
		}

		vec3 operator/( const float div ) const
		{
			return vec3( this->x / div, this->y / div, this->z / div );
		}
	};

	struct vec4 {
		vec4( ) = default;
		constexpr vec4( float xyzw ) : x( xyzw ), y( xyzw ), z( xyzw ), w( xyzw ) { };
		constexpr vec4( float x, float y ) : x( x ), y( y ), z( x ), w( y ) { };
		constexpr vec4( float x, float y, float z, float w ) : x( x ), y( y ), z( z ), w( w ) { };

		float x, y, z, w;
	};

	struct box {
		box( ) = default;
		constexpr box( int xywh ) : x( xywh ), y( xywh ), w( xywh ), h( xywh ) { };
		constexpr box( int x, int y ) : x( x ), y( y ), w( x ), h( y ) { };
		constexpr box( int x, int y, int w, int h ) : x( x ), y( y ), w( w ), h( h ) { };

		int x, y, w, h;
	};
}