
#include "triangle.hpp"
#include <mlib/minmax.hpp>
using namespace mlib;

namespace rt2
{
        Triangle::Triangle(vec4 a, vec4 b, vec4 c)
	{
		v0 = a;
		v1 = b;
		v2 = c;
                e1 = v0 - v1;
                e2 = v2 - v0;
                normal = cross(e1, e2);
        }

        void Triangle::operator = (const Triangle & t)
        {
                v0 = t.v0;
                v1 = t.v1;
                v2 = t.v2;
                normal = t.normal;
                e1 = t.e1;
                e2 = t.e2;
        }

        BBox Triangle::get_bbox()
        {
                return BBox(min(min(v0,v1),v2), max(max(v0,v1),v2));
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

        vec4 Triangle::get_normal(const vec4 & ) const
	{
                return normalize(normal);
	}

        float Triangle::crossing(const Ray & r)
	{
                vec4 pos = r.pos();
                vec4 dir = r.dir();
                vec4 t = v0 - pos;

                vec4 q = cross(dir, t);

                vec4 tmp (dot(t, normal), dot(e2, q), dot(e1, q), 0.0f);
                vec4 tuv = tmp * 1.0f / dot (dir, normal);

                int b = (tuv[1]>=0.0f && tuv[2]>=0.0f && tuv[0]>=0.0f && (tuv[1] + tuv[2] <= 1.0f));
                return b*tuv[0] + b - 1;
        }
}







