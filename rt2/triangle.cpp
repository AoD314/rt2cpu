
#include "triangle.hpp"

using namespace mlib;

namespace rt2
{
	Triangle::Triangle(vec4 a, vec4 b, vec4 c, vec4 n)
	{
		v0 = a;
		v1 = b;
		v2 = c;
		normal = n;
		e1 = v1 - v0;
		e2 = v2 - v0;
	}

	Triangle::Triangle(const Triangle & t)
	{
		v0 = t.v0;
		v1 = t.v1;
		v2 = t.v2;
		normal = t.normal;
                e1 = t.e1;
                e2 = t.e2;
	}

	vec4 Triangle::get_normal()
	{
		return normal;
	}

        void Triangle::get_points( mlib::vec4 & a, mlib::vec4 & b, mlib::vec4 & c)
        {
                a = v0;
                b = v1;
                c = v2;
        }

        float Triangle::crossing(const Ray & r)
	{
		vec4 pos = r.pos();
		vec4 dir = r.dir();

		vec4 t = pos - v0;

		vec4 q = cross ( t, e1 );
		vec4 p = cross ( dir, e2 );

		vec4 tmp (dot(q,e2), dot(p,t), dot(q, dir), 0.0f);
		vec4 tuv = tmp * 1.0f / dot (p, e1);

                if (tuv[0]>=0.0f && tuv[1]>=0.0f && tuv[2]>=0.0f && (tuv[1] + tuv[2] <= 1.0f))
                {
                        return tuv[0];
                }
                else
                {
                        return -1;
                }
	}
}

