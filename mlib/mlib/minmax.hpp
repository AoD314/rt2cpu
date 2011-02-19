
#ifndef __MINMAX_HPP__
#define __MINMAX_HPP__

#include "fixed_vector.hpp"

namespace mlib
{
	template <typename T>
	inline T abs ( T a )
	{
		return ( a > 0 ) ? a : -a;
	}

	template< typename T >
	inline T max ( T a, T b )
	{
		return ( a > b ) ? a : b;
	}

	template< typename T >
	inline T min ( T a, T b )
	{
		return ( a > b ) ? b : a;
	}

	template<typename T>
	inline void min_max ( T & a, T & b )
	{
		if ( a > b )
		{
			T temp = a;
			a = b;
			b = temp;
		}
	}

	template <>
	inline __m128 min ( __m128 a, __m128 b )
	{
		return _mm_min_ps (a, b);
	}

	template <>
	inline __m128 max ( __m128 a, __m128 b )
	{
		return _mm_max_ps ( a,b );
	}

        inline vec4 min ( vec4 & a, vec4 & b )
        {
                __m128 min = _mm_min_ps ( a.data, b.data );
                return vec4 ( min );
        }

        template<typename Left, typename Op, typename Right>
        inline vec4 min (const X<Left, Op, Right>& a, const X<Left, Op, Right>& b )
        {
                return min(vec4(a), vec4(b));
        }

        template<typename Left, typename Op, typename Right>
        inline vec4 min (vec4 & a, const X<Left, Op, Right>& b )
        {
                return min(a, vec4(b));
        }

        template<typename Left, typename Op, typename Right>
        inline vec4 min (const X<Left, Op, Right>& a, vec4 & b )
        {
                return min(vec4(a), b);
        }

	inline vec4 max ( vec4 & a, vec4 & b )
	{
		__m128 max = _mm_max_ps ( a.data, b.data );
		return vec4 ( max );
	}

        template<typename Left, typename Op, typename Right>
        inline vec4 max (const X<Left, Op, Right>& a, const X<Left, Op, Right>& b )
        {
                return max(vec4(a), vec4(b));
        }

        template<typename Left, typename Op, typename Right>
        inline vec4 max (vec4 & a, const X<Left, Op, Right>& b )
        {
                return max(a, vec4(b));
        }

        template<typename Left, typename Op, typename Right>
        inline vec4 max (const X<Left, Op, Right>& a, vec4& b )
        {
                return max(vec4(a), b);
        }

}

#endif

