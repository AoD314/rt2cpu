
#include "ray.hpp"

namespace rt2
{
	Ray::Ray(mlib::vec4 pos, mlib::vec4 dir)
	{
		p = pos;
		d = dir;
	}

	Ray::Ray(const Ray & r)
	{
		p = r.pos();
		d = r.dir();
	}

	void Ray::operator = (const Ray & r)
	{
		p = r.pos();
		d = r.dir();
	}
}
