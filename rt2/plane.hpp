
#ifndef __PLANE_HPP__
#define __PLANE_HPP__

#include <mlib/fixed_vector.hpp>

#include "primitive.hpp"
#include "bbox.hpp"
#include "ray.hpp"

namespace rt2
{
        class Plane : public Primitive
        {
                private:
                        mlib::vec4 pos;
                        mlib::vec4 dir;
                        float D;
                public:
                        Plane(mlib::vec4 posision, mlib::vec4 direction);

                        virtual mlib::vec4 get_normal(const mlib::vec4 & point) const;
                        virtual float crossing(const Ray & r);
                        virtual BBox get_bbox();
        };

}

#endif
