
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

	float Sphere::get_crossing_point(Ray & r, vec4 & point)
	{
		vec4 rpos = r.pos();
		vec4 rdir = r.dir();
		float A = dot(rdir, rdir);
		float B = 2.0f * dot(rdir, rdir - pos);
		float C = dot(rpos - pos, rpos - pos);
		float t1 = (- B + sqrt(B*B - 4 * A * C)) / (2.0f * A);
		float t2 = (- B - sqrt(B*B - 4 * A * C)) / (2.0f * A);
		float t = -1;
		if (t1 > 0.0f)
			if (t2 > 0.0f)
				t = min(t1,t2);
			else
				t = t1;
		if (t2 > 0.0f && t1 < 0.0f)
			t = t2;

		point = r.pos() * t + r.dir();

		return t;
	}

	bool Sphere::is_cross(Ray & r)
	{
		vec4 rpos = r.pos();
		vec4 rdir = r.dir();
		float A = dot(rdir, rdir);
		float B = 2.0f * dot(rdir, rdir - pos);
		float C = dot(rpos - pos, rpos - pos);
		float t1 = (- B + sqrt(B*B - 4 * A * C)) / (2.0f * A);
		float t2 = (- B - sqrt(B*B - 4 * A * C)) / (2.0f * A);
		return t1 + t2 > 0;
	}

	vec4 Sphere::get_normal(const mlib::vec4 & point)
	{
		return normalize(point - pos);
	}

}
