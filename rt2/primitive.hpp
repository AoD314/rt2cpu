
#ifndef __PRIMITIVE_HPP__
#define __PRIMITIVE_HPP__

#include <mlib/fixed_vector.hpp>

#include "bbox.hpp"
#include "ray.hpp"

namespace rt2
{
        class BBox;

        class Primitive
        {
                public:
                        virtual mlib::vec4 get_normal(const mlib::vec4 & point) const = 0;
                        virtual float crossing(const Ray & r) = 0;
                        virtual BBox get_bbox() = 0;
        };
}

#endif
