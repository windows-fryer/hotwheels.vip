//
// Created by liga on 7/5/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_MATH_HPP
#define HOTWHEELS_CSGO_EXTERNAL_MATH_HPP

#define NOMINMAX

#include <cmath>
#include <directxmath.h>

#include "../../sdk/structs/matrix.hpp"
#include "../../sdk/structs/vector.hpp"

#define PI           3.14159265358979323846f
#define RADPI        57.295779513082f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )

namespace math
{
	sdk::vector vector_to_angle( const sdk::vector& forward );

	sdk::vector angle_to_vector( const sdk::vector& angle );

	void angle_to_vector( const sdk::vector& angle, sdk::vector* forward, sdk::vector* right, sdk::vector* up );

	sdk::vector vector_transform( const sdk::vector& vector1, const sdk::matrix_3x4& matrix );

	float get_fov( const sdk::vector& view_angles, const sdk::vector& start, const sdk::vector& end );

	float calculate_angle_fov( const sdk::vector& ang1, const sdk::vector& ang2 );

	std::pair< sdk::vector, bool > world_to_screen( sdk::vector position );
} // namespace math

#endif // HOTWHEELS_CSGO_EXTERNAL_MATH_HPP
