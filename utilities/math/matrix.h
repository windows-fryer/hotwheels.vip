#pragma once

#include <limits>

#include "vector.h"

namespace math
{
    class c_matrix4x4 {
    public:
        float m[ 4 ][ 4 ];

        float* operator[]( const int i ) {
            return m[ i ];
        }
        const float* operator[]( const int i ) const {
            return m[ i ];
        }

        float* base( ) {
            return &m[ 0 ][ 0 ];
        }
        const float* base( ) const {
            return &m[ 0 ][ 0 ];
        }
    };

    class c_matrix3x4 {
    public:
        c_matrix3x4( ) = default;

        c_matrix3x4( float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22,
            float m23 ) {
            m_mat_val[ 0 ][ 0 ] = m00;
            m_mat_val[ 0 ][ 1 ] = m01;
            m_mat_val[ 0 ][ 2 ] = m02;
            m_mat_val[ 0 ][ 3 ] = m03;
            m_mat_val[ 1 ][ 0 ] = m10;
            m_mat_val[ 1 ][ 1 ] = m11;
            m_mat_val[ 1 ][ 2 ] = m12;
            m_mat_val[ 1 ][ 3 ] = m13;
            m_mat_val[ 2 ][ 0 ] = m20;
            m_mat_val[ 2 ][ 1 ] = m21;
            m_mat_val[ 2 ][ 2 ] = m22;
            m_mat_val[ 2 ][ 3 ] = m23;
        }

        //-----------------------------------------------------------------------------
        // Creates a matrix where the X axis = forward
        // the Y axis = left, and the Z axis = up
        //-----------------------------------------------------------------------------
        void init( const math::vec3& x_axis, const math::vec3& y_axis, const math::vec3& z_axis, const math::vec3& vec_origin ) {
            m_mat_val[ 0 ][ 0 ] = x_axis.x;
            m_mat_val[ 0 ][ 1 ] = y_axis.x;
            m_mat_val[ 0 ][ 2 ] = z_axis.x;
            m_mat_val[ 0 ][ 3 ] = vec_origin.x;
            m_mat_val[ 1 ][ 0 ] = x_axis.y;
            m_mat_val[ 1 ][ 1 ] = y_axis.y;
            m_mat_val[ 1 ][ 2 ] = z_axis.y;
            m_mat_val[ 1 ][ 3 ] = vec_origin.y;
            m_mat_val[ 2 ][ 0 ] = x_axis.z;
            m_mat_val[ 2 ][ 1 ] = y_axis.z;
            m_mat_val[ 2 ][ 2 ] = z_axis.z;
            m_mat_val[ 2 ][ 3 ] = vec_origin.z;
        }

        //-----------------------------------------------------------------------------
        // Creates a matrix where the X axis = forward
        // the Y axis = left, and the Z axis = up
        //-----------------------------------------------------------------------------
        c_matrix3x4( const math::vec3& x_axis, const math::vec3& y_axis, const math::vec3& z_axis, const math::vec3& vec_origin ) {
            init( x_axis, y_axis, z_axis, vec_origin );
        }

        void set_origin( const math::vec3& p ) {
            m_mat_val[ 0 ][ 3 ] = p.x;
            m_mat_val[ 1 ][ 3 ] = p.y;
            m_mat_val[ 2 ][ 3 ] = p.z;
        }

        void invalidate( ) {
            for ( auto& i : m_mat_val ) {
                for ( float& j : i )
                    j = std::numeric_limits<float>::infinity( );
            }
        }

        float* operator[]( int32_t i ) {
            return m_mat_val[ i ];
        }

        const float* operator[]( int32_t i ) const {
            return m_mat_val[ i ];
        }

        float* base( ) {
            return &m_mat_val[ 0 ][ 0 ];
        }

        const float* base( ) const {
            return &m_mat_val[ 0 ][ 0 ];
        }

        float m_mat_val[ 3 ][ 4 ];
    };
}