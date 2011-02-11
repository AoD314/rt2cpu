
#include "bvh.hpp"

#include <mlib/float.hpp>
using namespace mlib;

namespace rt2
{
        BVH::BVH(std::vector<Triangle> storage)
        {

        }

        Triangle * BVH::crossing(const Ray &ray, float &t)
        {
                float t_one, t_two = -1;

                Triangle * obj_one;
                Triangle * obj_two;

                if (one == NULL && two == NULL)
                {
                        size_t index = -1;
                        t = Float::MaxValue();

                        for (size_t i = 0; i < local_storage.size(); i++)
                        {
                                float lt = local_storage[i].crossing(ray);

                                if (lt >= 0.0f && lt < t)
                                {
                                        t = lt;
                                        index = i;
                                }
                        }

                        if (index == -1) return NULL;
                        return &local_storage[index];
                }

                if (one != NULL)
                {
                        obj_one = one->crossing(ray, t_one);
                }
                if (two != NULL)
                {
                        obj_two = two->crossing(ray, t_two);
                }

                if (t_one >= 0.0f && t_one > t_two)
                {
                        t = t_one;
                        return obj_one;
                }

                if (t_two >= 0.0f && t_two > t_one)
                {
                        t = t_two;
                        return obj_two;
                }

                return NULL;
        }


}

