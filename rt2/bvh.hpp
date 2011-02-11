
#ifndef __BVH_HPP__
#define __BVH_HPP__

#include <vector>

#include "triangle.hpp"
#include "ray.hpp"

namespace rt2
{
        class BVH
        {
                private:
                        BVH * one;
                        BVH * two;

                        std::vector<Triangle> local_storage;

                public:
                        BVH(std::vector<Triangle> storage);

                        Triangle * crossing(const Ray & ray, float & t);

        };
}

#endif
