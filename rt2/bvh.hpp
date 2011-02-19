
#ifndef __BVH_HPP__
#define __BVH_HPP__

#include <vector>

#include "triangle.hpp"
#include "ray.hpp"
#include "bbox.hpp"

namespace rt2
{
        class BVH
        {
                private:
                        BVH * one;
                        BVH * two;
                        BBox * box;

                        std::vector<Triangle> local_storage;

                public:
                        BVH(std::vector<Triangle> storage, int max_count_objects_in_bvh);
                        BVH(const BVH & bvh);

                        Triangle * crossing(const Ray & ray, float & t);
        };
}

#endif
