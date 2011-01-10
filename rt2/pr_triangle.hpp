
#ifndef __pr_triangle_hpp__
#define __pr_triangle_hpp__

#include "primitives.hpp"

#include <mlib/fixed_vector.hpp>
#include <mlib/minmax.hpp>

namespace primitives
{
    using namespace mlib;

    class Triangle : public Primitives
    {
        private:
            vec4 V0;
            vec4 V1;
            vec4 V2;

            vec4 normal;

        public:
            Triangle();

            Triangle(vec4& V0_d, vec4& V1_d, vec4& V2_d);

            void SetCoordinate(vec4& V0_d, vec4& V1_d, vec4& V2_d);

            void SetNormal(vec4 norm);

            explicit Triangle( const Triangle & tr);

            float Crossing (Ray& r, vec4& tp);

            vec4 GetMin();

            vec4 GetMax();

            inline vec4 CalcNormal (vec4& tp);
    };

}

#endif

