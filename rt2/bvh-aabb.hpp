
#ifndef __bvh_aabb_hpp__
#define __bvh_aabb_hpp__

#include <math.h>
#include <vector>
#include <limits>


#include "material.hpp"
#include "pr_triangle.hpp"
#include "smath.hpp"
#include "ray.hpp"
#include "boundingvolume.hpp"
#include "primitives.hpp"

using namespace material;
using namespace ray;

#include <mlib/fixed_vector.hpp>
using namespace mlib;


namespace primitives
{
        struct NodeBVH
        {
                BoundingVolume bv;
                std::vector<Primitives*> list;

                NodeBVH * left;
                NodeBVH * right;
        };

        class BVH
        {
                protected:
                        NodeBVH * root;
                        std::size_t depth;


                        Primitives * BoxCrossing (Ray & r, vec4& point, NodeBVH * node);

                public:

                        BVH(Primitives ** p, std::size_t size, std::size_t depth = 4);

                        Primitives * crossing (Ray & r, vec4& point);

        };

}

#endif

