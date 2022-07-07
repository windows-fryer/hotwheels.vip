//
// Created by liga on 7/5/2022.
//

#include "math.hpp"
#include "../../sdk/structs/offsets.hpp"
#include "../driver/driver.hpp"

void math::angle_to_vector( const sdk::vector& angle, sdk::vector* forward, sdk::vector* right, sdk::vector* up )
{
	float sp, sy, sr, cp, cy, cr;

	DirectX::XMScalarSinCos( &sp, &cp, DEG2RAD( angle.x ) );
	DirectX::XMScalarSinCos( &sy, &cy, DEG2RAD( angle.y ) );
	DirectX::XMScalarSinCos( &sr, &cr, DEG2RAD( angle.z ) );

	if ( forward != nullptr ) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if ( right != nullptr ) {
		right->x = -1 * sr * sp * cy + -1 * cr * -sy;
		right->y = -1 * sr * sp * sy + -1 * cr * cy;
		right->z = -1 * sr * cp;
	}

	if ( up != nullptr ) {
		up->x = cr * sp * cy + -sr * -sy;
		up->y = cr * sp * sy + -sr * cy;
		up->z = cr * cp;
	}
}

sdk::vector math::angle_to_vector( const sdk::vector& angle )
{
	const auto sy = std::sin( angle.y / 180.f * PI );
	const auto cy = std::cos( angle.y / 180.f * PI );

	const auto sp = std::sin( angle.x / 180.f * PI );
	const auto cp = std::cos( angle.x / 180.f * PI );

	return sdk::vector( cp * cy, cp * sy, -sp );
}

sdk::vector math::vector_to_angle( const sdk::vector& forward )
{
	float pitch, yaw, buffer;

	if ( forward.y == 0 && forward.x == 0 ) {
		yaw = 0;

		if ( forward.z > 0 )
			pitch = 270;
		else
			pitch = 90;
	} else {
		yaw = RAD2DEG( atan2f( forward.y, forward.x ) );

		if ( yaw < 0 )
			yaw += 360;

		buffer = forward.length_2d( );

		pitch = RAD2DEG( atan2f( -forward.z, buffer ) );

		if ( pitch < 0 )
			pitch += 360;
	}

	return { pitch, yaw, 0 };
}

sdk::vector math::vector_transform( const sdk::vector& vector1, const sdk::matrix_3x4& matrix )
{
	sdk::vector output{ };

	for ( int i = 0; i < 3; i++ )
		output[ i ] = vector1.dot( matrix.data[ i ] ) + matrix.data[ i ][ 3 ];

	return output;
}

float math::get_fov( const sdk::vector& view_angles, const sdk::vector& start, const sdk::vector& end )
{
	sdk::vector forward, direction = ( end - start ).normalized( );

	forward = angle_to_vector( view_angles );

	return std::max( RAD2DEG( std::acos( forward.dot_product( direction ) ) ), 0.f );
}

float math::calculate_angle_fov( const sdk::vector& ang1, const sdk::vector& ang2 )
{
	sdk::vector ang, aim;

	aim = angle_to_vector( ang1 );
	ang = angle_to_vector( ang2 );

	return RAD2DEG( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
}

std::pair< sdk::vector, bool > math::world_to_screen( sdk::vector position )
{
	static auto client_dll = driver::base_address( "client.dll" );

	const auto matrix = driver::read< sdk::view_matrix >( reinterpret_cast< PVOID >( client_dll + offsets::view_matrix ) );

	if ( !matrix.data ) {
		return { { }, false };
	}

	float width = matrix[ 3 ][ 0 ] * position.x + matrix[ 3 ][ 1 ] * position.y + matrix[ 3 ][ 2 ] * position.z + matrix[ 3 ][ 3 ];

	if ( width < 0.001f ) {
		return { { }, false };
	}

	float inverse = 1.f / width;

	sdk::vector screen;

	screen.x = ( matrix[ 0 ][ 0 ] * position.x + matrix[ 0 ][ 1 ] * position.y + matrix[ 0 ][ 2 ] * position.z + matrix[ 0 ][ 3 ] ) * inverse;
	screen.y = ( matrix[ 1 ][ 0 ] * position.x + matrix[ 1 ][ 1 ] * position.y + matrix[ 1 ][ 2 ] * position.z + matrix[ 1 ][ 3 ] ) * inverse;

	auto screen_size = sdk::vector{ 1920, 1080 };

	screen.x = ( screen_size.x * 0.5f ) + ( screen.x * screen_size.x ) * 0.5f;
	screen.y = ( screen_size.y * 0.5f ) - ( screen.y * screen_size.y ) * 0.5f;

	return { sdk::vector( static_cast< int >( screen.x ), static_cast< int >( screen.y ) ), true };
}