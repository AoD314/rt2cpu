
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
	}

	Triangle::Triangle(const Triangle & t)
	{
		v0 = t.v0;
		v1 = t.v1;
		v2 = t.v2;
		normal = t.normal;
	}

	vec4 Triangle::get_normal()
	{
		return normal;
	}

	float Triangle::crossing(Ray & r, vec4 & point)
	{
		vec4 pos = r.pos();
		vec4 dir = r.dir();

		vec4 e1 = v1 - v0;
		vec4 e2 = v2 - v0;
		vec4 t = pos - v0;

		vec4 q = cross ( t, e1 );
		vec4 p = cross ( dir, e2 );

		vec4 tmp (dot(q,e2), dot(p,t), dot(q, dir), 0.0f);
		vec4 tuv = tmp * 1.0f / dot (p, e1);

		if (tuv[0]>=0.0f && tuv[1]>=0.0f && tuv[2]>=0.0f && (tuv[1] + tuv[2] <= 1.0f))
		{
			point = pos + tuv[0] * dir;
			return tuv[0];
		}

		return -1.0f;
	}
}

