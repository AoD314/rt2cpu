
#ifndef __ray_hpp__
#define __ray_hpp__

#include <mlib/fixed_vector.hpp>
using namespace mlib;

namespace ray
{

        class Ray
        {
                private:
                        vec4 pos;

                        vec4 direction;

                public:
                        Ray(vec4& p, vec4& d);

                        Ray();

                        vec4& Position();

                        vec4& Direction();

        };

}

#endif

