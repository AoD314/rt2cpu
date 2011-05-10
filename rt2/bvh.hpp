
#ifndef __BVH_HPP__
#define __BVH_HPP__

#include <vector>

#include "primitive.hpp"
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

                        std::vector<Primitive *> local_storage;

                public:
                        BVH(std::vector<Primitive *> storage, int max_count_objects_in_bvh);
                        BVH(const BVH & bvh);

                        Primitive * crossing(const Ray & ray, float & t);
                        ~BVH();
        };
}

#endif
