
#include "sphere.hpp"

#include <mlib/minmax.hpp>
using namespace mlib;

namespace rt2
{
	Sphere::Sphere(mlib::vec4 position, float radius)
	{
		pos = position;
		rad = radius;
	}

        Sphere::Sphere(const Sphere & s)
        {
            pos = s.pos;
            rad = s.rad;
        }

        void Sphere::operator = (const Sphere & s)
        {
            pos = s.pos;
            rad = s.rad;
        }

        BBox Sphere::get_bbox()
        {
                return BBox(vec4::zero(), vec4::zero());
        }

        float Sphere::crossing(const Ray & r)
	{
                vec4 rd(r.dir());
                vec4 rp(r.pos());
                float A = dot(rd, rd);
                float B = 2.0f * dot(rd, rp - pos);
                float D = B * B - 4.0f * A * (dot(rp - pos, rp - pos) - rad * rad);
                if (D >= 0.0f)
                {
                        float t1 = (- B + sqrt(D)) / (2.0f * A);
                        float t2 = (- B - sqrt(D)) / (2.0f * A);

                        float t = -1;
                        if (t1 > 0.0f)
                                if (t2 > 0.0f)
                                        t = min(t1,t2);
                                else
                                        t = t1;
                        if (t2 > 0.0f && t1 < 0.0f)
                                t = t2;

                        if (t >= 0.0f)
                        {
                                return t;
                        }
                }
                else
                        return -1;
	}

        vec4 Sphere::get_normal(const mlib::vec4 & point) const
	{
		return normalize(point - pos);
	}

}
