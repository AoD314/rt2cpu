
#include "boundingvolume.hpp"

namespace primitives
{

        BoundingVolume::BoundingVolume(vec4 one, vec4 two)
        {
                point_min = one;
                point_max = two;
        }

        BoundingVolume::BoundingVolume()
        {
                point_min.zero ();
                point_max.zero ();
        }

        BoundingVolume BoundingVolume::split(std::size_t num)
        {
                vec4 delta = point_max - point_min;

                float max = Abs (delta[0]);
                int os = 0;

                if ( Abs (delta[1]) > max)
                {
                        max =  Abs (delta[1]);
                        os = 1;
                }

                if ( Abs (delta[2]) > max)
                {
                        max =  Abs (delta[2]);
                        os = 2;
                }

                max /= 2;

                delta.set1(max);

                BoundingVolume b1(point_min, point_min + delta);

                delta(0, 0.0f);
                delta(1, 0.0f);
                delta(2, 0.0f);
                delta(os, max);

                BoundingVolume b2(point_min + delta, point_max);

                if (num == 0)
                        return b1;
                else
                        return b2;
        }

        bool BoundingVolume::is_crossing_b( BoundingVolume & bv )
        {
                vec4 p0_min, p0_max;
                p0_max = bv.point_min;
                p0_min = bv.point_max;

                return true;
        }

        bool BoundingVolume::is_crossing_r( Ray & r, float &near, float &far)
        {
                vec4 pos, ext;
                ext = (point_max - point_min);
                pos = (point_max + point_min);

                ext = ext * 0.5f;
                pos = pos * 0.5f;

                near = 0;
                far = 0;

                float t1,t2;

                t1 = (pos[0] - ext[0]) / r.Direction()[0];
                t2 = (pos[0] + ext[0]) / r.Direction()[0];

                float tnear = Min(t1, t2);
                float tfar  = Max(t1, t2);

                near = Min(near, tnear);
                far  = Max(far, tfar);


                t1 = (pos[1] - ext[1]) / r.Direction()[1];
                t2 = (pos[1] + ext[1]) / r.Direction()[1];

                tnear = Min(t1, t2);
                tfar  = Max(t1, t2);

                near = Min(near, tnear);
                far  = Max(far, tfar);

                t1 = (pos[2] - ext[2]) / r.Direction ()[2];
                t2 = (pos[2] + ext[2]) / r.Direction ()[2];

                tnear = Min(t1, t2);
                tfar  = Max(t1, t2);

                near = Min(near, tnear);
                far  = Max(far, tfar);

                if (far <= near) return false;

                return true;
        }


        vec4 BoundingVolume::get_point_one()
        {
                return point_min;
        }

        vec4 BoundingVolume::get_point_two()
        {
                return point_max;
        }

        void BoundingVolume::set_point_one(vec4 p1)
        {
                point_min = p1;
        }

        void BoundingVolume::set_point_two(vec4 p2)
        {
                point_max = p2;
        }


}

