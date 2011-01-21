
#ifndef __BBOX_HPP__
#define __BBOX_HPP__

#include "ray.hpp"

#include <mlib/fixed_vector.hpp>

namespace rt2
{
	class BBox
	{
		private:
			mlib::vec4 bmin, bmax;

		public:
			BBox ( mlib::vec4 mn, mlib::vec4 mx);
			bool is_cross(Ray & r);
	
	};
}

#endif

