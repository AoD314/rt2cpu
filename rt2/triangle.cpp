
#include "triangle.hpp"

namespace rt2
{
	Triangle::Triangle(mlib::vec4 a, mlib::vec4 b, mlib::vec4 c)
	{
		v0 = a;
		v1 = b;
		v2 = c;
	}

	bool Triangle::is_cross(Ray & r)
	{
		mlib::vec4 pos = r.pos();
		mlib::vec4 dir = r.dir();

		mlib::vec4 e1 = v1 - v0;
		mlib::vec4 e2 = v2 - v0;
		mlib::vec4 t = pos - v0;

		mlib::vec4 q = cross ( t, e1 );
		mlib::vec4 p = cross ( dir, e2 );

		mlib::vec4 tmp (dot(q,e2), dot(p,t), dot(q, dir), 0.0f);
		mlib::vec4 tuv = tmp * 1.0f / dot (p, e1);

		if (tuv[0]>=0 && tuv[1]>=0 && tuv[2]>=0 && (tuv[1] + tuv[2] <= 1.0f))
		{
			return true;
		}

		return false;
	}
}

