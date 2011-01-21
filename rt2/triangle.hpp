
#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include <mlib/fixed_vector.hpp>

#include "ray.hpp"

namespace rt2
{

	class Triangle
	{
		private:
			mlib::vec4 v0, v1, v2;

		public:
			Triangle(mlib::vec4 a, mlib::vec4 b, mlib::vec4 c);

			float crossing(Ray & r, mlib::vec4 & point);
	
	};


}

#endif

