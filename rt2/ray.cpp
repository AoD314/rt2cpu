
#include "ray.hpp"

namespace rt2
{
	Ray::Ray(mlib::vec4 pos, mlib::vec4 dir)
	{
		p = pos;
		d = dir;
	}
	
	mlib::vec4 Ray::pos()
	{
		return p;
	}

	mlib::vec4 Ray::dir()
	{
		return d; 
	}
}

