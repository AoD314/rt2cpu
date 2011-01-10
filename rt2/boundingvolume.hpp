
#ifndef __boundingvolume_hpp__
#define __boundingvolume_hpp__

#include "ray.hpp"
using namespace ray;

#include <math.h>

#include <mlib/fixed_vector.hpp>
#include <mlib/minmax.hpp>
using namespace mlib;


namespace primitives
{
        class BoundingVolume
        {
                private:
                        vec4 point_min;
                        vec4 point_max;

                public:
                        BoundingVolume(vec4 one, vec4 two);
                        BoundingVolume();

                        BoundingVolume split(std::size_t num);

                        vec4 get_point_one();
                        vec4 get_point_two();

                        bool is_crossing_b( BoundingVolume & bv );
                        bool is_crossing_r( Ray & r, float &near, float &far);

                        void set_point_one(vec4 p1);
                        void set_point_two(vec4 p2);
        };

}

#endif

