
#ifndef __primitives_hpp__
#define __primitives_hpp__

#include <math.h>

#include "material.hpp"
#include "smath.hpp"
#include "ray.hpp"

using namespace material;
using namespace ray;

#include <mlib/fixed_vector.hpp>
using namespace mlib;

namespace primitives
{
    class Primitives
    {
        protected:
            vec4 position;

            vec4 orientation;

            Material* mtr;

        public:

            Primitives();

            Primitives(vec4& _p, vec4& _d);

            void Move(vec4& np)
            {
                position = np;
            }

            virtual float Crossing (Ray& r, vec4& tp) = 0;

            virtual vec4 CalcNormal (vec4& tp) = 0;

            Material* Materials();

            void SetMaterial(Material* m);
    };

}

#endif

