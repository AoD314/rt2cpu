
#ifndef __FIXED_VECTOR_HPP__
#define __FIXED_VECTOR_HPP__

#include "mmemory.hpp"
#include <math.h>
#include <iostream>

namespace mlib
{
        ///////////////////////////////
        ///////// control sse /////////
        ///////////////////////////////

        #include <xmmintrin.h>
        #include <mmintrin.h>
        #include <pmmintrin.h>
        #include <smmintrin.h>

        ///////////////////////////////
        ///////////////////////////////
        ///////////////////////////////

        #ifndef WIN32
                #define _align_ __attribute__((aligned(16)))
        #else
                #define _align_ __declspec(align(16))
        #endif

        ///////////////////////////////
        ///////////////////////////////
        ///////////////////////////////

        template <typename Left, typename Op, typename Right>
        struct X;

        ///////////////////////////////
        ///////////////////////////////
        ///////////////////////////////

        struct vec4
        {
            _align_ __m128 data;

            template<typename Left, typename Op, typename Right >
            vec4 (const X<Left, Op, Right> & expression)
            {
                data = expression();
            }

            vec4 ()
            {
                data = _mm_set1_ps(0.0f);
            }

            void set1(const float val)
            {
                data = _mm_set1_ps(val);
            }

            vec4 (const float val)
            {
                set1(val);
            }

            void set (float x, float y, float z, float w)
            {
                data = _mm_setr_ps(x,y,z,w);
            }

            vec4 (float x, float y, float z, float w)
            {
                set(x,y,z,w);
            }

            vec4 (const vec4 & v)
            {
                data = v.data;
            }

            vec4 (const __m128 d)
            {
                data = d;
            }

            inline vec4(const float * data_a)
            {
                data = _mm_load1_ps(data_a);
            }

            template<typename Left, typename Op, typename Right>
            inline void operator = (const X<Left, Op, Right>& expression)
            {
                data = expression();
            }

            inline void operator = (const vec4 & val)
            {
                data = val.data;
            }

            template<typename Left, typename Op, typename Right>
            inline void operator += (const X<Left, Op, Right>& expression)
            {
                data = _mm_add_ps(data, expression());
            }

            template<typename Left, typename Op, typename Right>
            inline void operator -= (const X<Left, Op, Right>& expression)
            {
                data = _mm_sub_ps(data, expression());
            }

            inline float operator[] (std::size_t i) const
            {
                _align_ float d[4];
                _mm_store_ps(&d[0], data);
                return d[i];
            }

            inline void operator() (std::size_t i, float val)
            {
                _align_ float d[4];
                _mm_store_ps(&d[0], data);
                d[i] = val;
                data = _mm_load1_ps(&d[0]);
            }

            inline void zero()
            {
                data = _mm_set1_ps(0.0f);
            }

            inline void one()
            {
                data = _mm_set1_ps(1.0f);
            }

            inline void normalize()
            {
                __m128 m = _mm_dp_ps(data, data, 0xFF);
                _align_ float d[4];
                _mm_store_ps(&d[0], m);
                d[0] = 1.0 / sqrt(d[0]);
                data = _mm_mul_ps(data, _mm_set1_ps(d[0]));
            }

            inline void clamp(float min, float max)
            {
                data = _mm_min_ps(_mm_set1_ps(max), data);
                data = _mm_max_ps(_mm_set1_ps(min), data);
            }

        };

        ///////////////////////////////////////////
        /// - - - - - - Dot product - - - - - - ///
        ///////////////////////////////////////////

        inline float dot(const vec4 & a, const vec4 & b)
        {
            _align_ float res;
            _align_ __m128 m3;
            m3 = _mm_dp_ps(a.data, b.data, 0x55);
            _mm_store_ss(&res, m3);
            return res;
        }

        template <typename Left, typename Op, typename Right>
        inline float dot(const vec4 & a, const X<Left, Op, Right> & b)
        {
            return dot( a, vec4(b) );
        }

        template <typename Left, typename Op, typename Right>
        inline float dot(const X<Left, Op, Right> & a, const vec4 & b)
        {
            return dot(vec4(a), b);
        }

        template <typename Left1, typename Left2, typename Op1, typename Op2, typename Right1, typename Right2>
        inline float dot(const X<Left1, Op1, Right1> & a, const X<Left2, Op2, Right2> & b)
        {
            return dot(vec4 (a), vec4 (b));
        }

        ///////////////////////////////////////////
        /// - - - - - - Normalize - - - - - - - ///
        ///////////////////////////////////////////

        inline vec4 Normalize(const vec4 & a)
        {
            vec4 v(a);
            v.normalize();
            return v;
        }

        template <typename Left, typename Op, typename Right>
        inline vec4 Normalize(const X<Left, Op, Right> & a)
        {
            return Normalize( vec4(a) );
        }

        ///////////////////////////////////////////
        /// - - - - - - std::ostream& - - - - - ///
        ///////////////////////////////////////////

        inline std::ostream & operator << ( std::ostream& out, const vec4 & x )
        {
            float v[4];
            _mm_store_ps(v, x.data);

            for (size_t i = 0; i < 4; i++)
                    out << v[i] << " ";
            return out;
        }

        ///////////////////////////////////////////
        /// - - - - - - CalcDistance - - - - - -///
        ///////////////////////////////////////////

        inline float  CalcDistance(const vec4 & a, const vec4 & b)
        {
            __m128 r = _mm_sub_ps(a.data, b.data);
            return sqrt(dot(r, r));
        }

        template <typename Left, typename Op, typename Right>
        inline float  CalcDistance(const X<Left, Op, Right> & a, const X<Left, Op, Right> & b)
        {
                return CalcDistance(vec4(a), vec4(b));
        }

        template <typename Left, typename Op, typename Right>
        inline float CalcDistance(const X<Left, Op, Right> & a, const vec4 & b)
        {
                return CalcDistance(vec4(a), b);
        }

        template <typename Left, typename Op, typename Right>
        inline float  CalcDistance(const vec4 & a, const X<Left, Op, Right> & b)
        {
                return CalcDistance(a, vec4(b));
        }

        ///////////////////////////////////////////
        /// - - - - - - - Cross - - - - - - - - ///
        ///////////////////////////////////////////

        inline vec4 Cross(const vec4 & v1, const vec4 & v2)
        {
                __m128 a, b, c;

                a = _mm_shuffle_ps(v1.data, v1.data, 0xC9); /// 11 00 10 01
                b = _mm_shuffle_ps(v2.data, v2.data, 0xD2); /// 11 01 00 10
                c = _mm_mul_ps(a, b);

                a = _mm_shuffle_ps(v1.data, v1.data, 0xD2); /// 11 01 00 10
                b = _mm_shuffle_ps(v2.data, v2.data, 0xC9); /// 11 00 10 01
                a = _mm_mul_ps(a, b);

                c = _mm_sub_ps(c, a);

                return c;
        }

        template <typename Left, typename Op, typename Right>
        inline vec4 Cross(const X<Left, Op, Right> & v1, const X<Left, Op, Right> & v2)
        {
            return Cross(vec4(v1), vec4(v2));
        }

        template <typename Left, typename Op, typename Right>
        inline vec4 Cross(const X<Left, Op, Right> & v1, const vec4 & v2)
        {
                return Cross(vec4(v1), v2);
        }

        template <typename Left, typename Op, typename Right>
        inline vec4 Cross(const vec4 & v1, const X<Left, Op, Right> & v2)
        {
                return Cross(v1, vec4(v2));
        }


        ///////////////////////////////////////////
        /// - - - - - - - ToColor - - - - - - - ///
        ///////////////////////////////////////////
        ///////////////////////////////////////////

        inline std::size_t ToColor(vec4& color)
        {
                std::size_t r;

                __m128 a, b;

                b = color.data;
                a = _mm_set1_ps(255.0f);

                b = _mm_mul_ps(b, a);
                b = _mm_min_ps(b, a);

                float q[4];
                _mm_storeu_ps(q, b);

                r =		((std::size_t) q[0]*(1 << 16)) +
                                ((std::size_t) q[1]*(1 << 8)) +
                                ((std::size_t) q[2]);

                return r;
        }

        ///////////////////////////////////////////
        /// - - - - - struct operations - - - - ///
        ///////////////////////////////////////////

        struct plus
        {
            static inline __m128 apply(const __m128 a, const __m128 b)
            {
                return _mm_add_ps(a, b);
            }
        };

        struct minus
        {
            static inline __m128 apply(const __m128 &a, const __m128 & b)
            {
                return _mm_sub_ps(a, b);
            }
        };

        struct mul
        {
            static inline __m128 apply(const __m128 & a, const __m128 & b)
            {
                return _mm_mul_ps(a, b);
            }
        };

        struct div
        {
            static inline __m128 apply(const __m128 & a, const __m128 & b)
            {
                return _mm_div_ps(a, b);
            }
        };

        ///////////////////////////////////////////
        /// - - - - - - -  struct X - - - - - - ///
        ///////////////////////////////////////////

        template <typename Left, typename Op, typename Right>
        struct X
        {
                X(Left t1, Right t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(lNode_(), rNode_());
                }

            private:
                const Right rNode_;
                const Left lNode_;
        };

        template <typename Left, typename Op>
        struct X<Left, Op, float>
        {

                X(Left t1, float t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(lNode_(), _mm_set1_ps(rNode_));
                }

        private:
                const float rNode_;
                const Left  lNode_;
        };

        template <typename Left, typename Op>
        struct X<Left, Op, __m128>
        {
                X(Left t1, __m128 t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(lNode_(), rNode_);
                }

        private:
                const __m128 rNode_;
                const Left   lNode_;
        };


        template <typename Op, typename Right>
        struct X<float, Op, Right>
        {
                X(float t1, Right t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(_mm_set1_ps(lNode_), rNode_());
                }

        private:
                const Right rNode_;
                const float lNode_;
        };

        template <typename Op, typename Right>
        struct X<__m128, Op, Right>
        {
                X(__m128 t1, Right t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(lNode_, rNode_());
                }

        private:
                const Right  rNode_;
                const __m128 lNode_;
        };


        template <typename Op>
        struct X<__m128, Op, __m128>
        {
                X(__m128 t1, __m128 t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(lNode_, rNode_);
                }

            private:
                const __m128 rNode_;
                const __m128 lNode_;
        };

        template <typename Op>
        struct X<float, Op, __m128>
        {
                X(float t1, __m128 t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(_mm_set1_ps(lNode_), rNode_);
                }

            private:
                const __m128 rNode_;
                const float lNode_;
        };

        template <typename Op>
        struct X<float, Op, float>
        {
                X(float t1, float t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(_mm_set1_ps(lNode_), _mm_set1_ps(rNode_));
                }

            private:
                const float rNode_;
                const float lNode_;
        };

        template <typename Op>
        struct X<__m128, Op, float>
        {
                X(__m128 t1, float t2) : lNode_(t1), rNode_(t2) { }

                __m128 operator() () const
                {
                        return Op::apply(lNode_, _mm_set1_ps(rNode_));
                }

            private:
                const float  rNode_;
                const __m128 lNode_;
        };

        ///////////////////////////////////////////
        /// - - - - - - define OP_BASE  - - - - ///
        ///////////////////////////////////////////


        #define OP_BASE(_OP_,_OP_Z)                                                                                 \
                                                                                                                    \
        template<typename Left, typename Right>                                                                     \
        inline X<Left, _OP_, Right> operator _OP_Z (const Left& a, const Right& b)                                  \
        {                                                                                                           \
                return X<Left, _OP_, Right>(a, b);                                                                  \
        }                                                                                                           \
                                                                                                                    \
        template<typename Left>                                                                                     \
        inline X<Left, _OP_, float> operator _OP_Z (const Left& a, const float& b)                                  \
        {                                                                                                           \
                return X<Left, _OP_, float>(a, b);                                                                  \
        }                                                                                                           \
                                                                                                                    \
        template<typename Left>                                                                                     \
        inline X<Left, _OP_, __m128>  operator _OP_Z (const Left& a, const vec4& b)		                    \
        {                                                                                                           \
                return X<Left, _OP_, __m128>(a, b.data);                                                            \
        }                                                                                                           \
                                                                                                                    \
        template<typename Right>                                                                                    \
        inline X<__m128, _OP_, Right> operator _OP_Z (const vec4& a, const Right& b)                                \
        {                                                                                                           \
                return X<__m128, _OP_, Right>(a.data, b);                                                           \
        }                                                                                                           \
                                                                                                                    \
        inline X<__m128, _OP_, float> operator _OP_Z (const vec4& a, const float& b)                                \
        {                                                                                                           \
                return X<__m128, _OP_, float>(a.data, b);                                                           \
        }                                                                                                           \
                                                                                                                    \
        inline X<float, _OP_, __m128> operator _OP_Z (const float& a, const vec4& b)                                \
        {                                                                                                           \
                return X<float, _OP_, __m128>(a, b.data);						            \
        }                                                                                                           \
                                                                                                                    \
        template<typename Right>                                                                                    \
        inline X<float, _OP_, Right> operator _OP_Z (const float& a, const Right& b)                                \
        {                                                                                                           \
                return X<float, _OP_, Right>(a, b);                                                                 \
        }                                                                                                           \
                                                                                                                    \
        inline X<__m128, _OP_, __m128> operator _OP_Z (const vec4& a, const vec4& b)                                \
        {                                                                                                           \
                return X<__m128, _OP_, __m128>(a.data, b.data);                                                     \
        }                                                                                                           \
                                                                                                                    \
        template                                                                                                    \
                        <                                                                                           \
                            typename Left1, typename Op1, typename Right1,                                          \
                            typename Left2, typename Op2, typename Right2                                           \
                        >                                                                                           \
        inline  X< X<Left1, Op1, Right1>, _OP_, X<Left2, Op2, Right2> >                                             \
        operator _OP_Z  (const  X<Left1, Op1, Right1>& a, const  X<Left2, Op2, Right2>& b)                          \
        {                                                                                                           \
                return X< X<Left1, Op1, Right1>, _OP_, X<Left2, Op2, Right2> >(a, b);                               \
        }


        OP_BASE(plus, +)

        OP_BASE(minus, -)

        OP_BASE(mul, *)

        OP_BASE(div, /)

}

#endif
