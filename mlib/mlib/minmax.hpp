
#ifndef __MINMAX_HPP__
#define __MINMAX_HPP__

#include "fixed_vector.hpp"

namespace mlib
{
template <typename T>
inline T Abs ( T a )
{
    return ( a > 0 ) ? a : -a;
}

template< typename T >
inline T Max ( T a, T b )
{
    return ( a > b ) ? a : b;
}

template< typename T >
inline T Min ( T a, T b )
{
    return ( a > b ) ? b : a;
}

template<typename T>
inline void MinMax ( T & a, T & b )
{
    if ( a > b )
    {
        T temp = a;
        a = b;
        b = temp;
    }
}

template <>
inline __m128 Min ( __m128 a, __m128 b )
{
    return _mm_min_ps ( a,b );
}

template <>
inline __m128 Max ( __m128 a, __m128 b )
{
    return _mm_max_ps ( a,b );
}

inline vec4 Min ( vec4 & a, vec4 & b )
{
    __m128 min = _mm_min_ps ( a.data, b.data );
    return vec4 ( min );
}

inline vec4 Max ( vec4 & a, vec4 & b )
{
    __m128 max = _mm_max_ps ( a.data, b.data );
    return vec4 ( max );
}
}

#endif
