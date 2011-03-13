
#include "plane.hpp"
#include <mlib/float.hpp>

using namespace mlib;

namespace rt2
{
        Plane::Plane(mlib::vec4 posision, mlib::vec4 direction)
        {
                pos = posision;
                dir = direction;
                D = - dot (pos, dir);
        }

        vec4 Plane::get_normal(const vec4 & point) const
        {
                return dir;
        }

        float Plane::crossing(const Ray & r)
        {
                float A = dot(dir, r.pos());
                float B = dot(dir, r.dir());
                if (B != 0.0f)
                {
                        return (A + D) / B;
                }

                return -1.0f;
        }

        BBox Plane::get_bbox()
        {
                return BBox(vec4(-Float::MaxValue()),vec4(Float::MaxValue()));
        }

}
