
#ifndef __PRIMITIVE_HPP__
#define __PRIMITIVE_HPP__

#include <mlib/fixed_vector.hpp>

#include "ray.hpp"

namespace rt2
{
        class Primitive
        {
                public:
                        virtual mlib::vec4 get_normal(const mlib::vec4 & point) const = 0;
                        virtual float crossing(const Ray & r) = 0;
        };
}

#endif
