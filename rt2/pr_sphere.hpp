
#ifndef __pr_sphere_hpp__
#define __pr_sphere_hpp__

#include "primitives.hpp"


#include <mlib/fixed_vector.hpp>
#include <mlib/minmax.hpp>
using namespace mlib;

namespace primitives
{

        class Sphere : public Primitives
        {
                private:
                        float rad;
                        float r2;

                public:
                        Sphere(float x, float y, float z, float r);

                        float Crossing (Ray& r, vec4& tp);

                        bool isCrossing (Ray& r);

                        inline vec4 CalcNormal (vec4& tp);

        };

}

#endif

