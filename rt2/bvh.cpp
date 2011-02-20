
#include "bvh.hpp"

#include <mlib/float.hpp>
using namespace mlib;

namespace rt2
{
        BVH::BVH(const BVH & bvh)
        {
                one = bvh.one;
                two = bvh.two;
                box = bvh.box;
                local_storage = bvh.local_storage;
        }

        BVH::BVH(std::vector<Triangle> storage, int max_count_objects_in_bvh)
        {
                box = new BBox(storage);
                if (storage.size() <= max_count_objects_in_bvh)
                {
                        local_storage = storage;
                        one = NULL;
                        two = NULL;
                        printf("storage = %d\n", storage.size());
                }
                else
                {
                        BBox boxl(box->get_split_point(split_min), box->get_max_point());
                        BBox boxr(box->get_min_point(), box->get_split_point(split_max));

                        std::vector<Triangle> stl;
                        std::vector<Triangle> str;

                        for (size_t i = 0; i < storage.size(); i++)
                        {
                                if (boxl.in(storage[i]))
                                        stl.push_back(storage[i]);

                                if (boxr.in(storage[i]))
                                        str.push_back(storage[i]);
                        }
                        if (storage.size() == stl.size() || storage.size() == str.size())
                        {
                                local_storage = storage;
                                one = NULL;
                                two = NULL;
                                printf("storage = %d\n", storage.size());
                        }
                        else
                        {
                                one = new BVH(stl, max_count_objects_in_bvh);
                                two = new BVH(str, max_count_objects_in_bvh);
                        }
                }
        }


        Triangle * BVH::crossing(const Ray &ray, float &t)
        {
                if (box->is_cross(ray) == false)
                {
                        return NULL;
                }

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

                float t_one, t_two = -1;

                Triangle * obj_one;
                Triangle * obj_two;

                if (one != NULL)
                {
                        obj_one = one->crossing(ray, t_one);
                }
                if (two != NULL)
                {
                        obj_two = two->crossing(ray, t_two);
                }

                if (t_one >= 0.0f && t_one >= t_two)
                {
                        t = t_one;
                        return obj_one;
                }

                if (t_two >= 0.0f && t_two >= t_one)
                {
                        t = t_two;
                        return obj_two;
                }

                return NULL;
        }

}
