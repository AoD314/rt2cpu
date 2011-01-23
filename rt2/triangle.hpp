
#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include <mlib/fixed_vector.hpp>

#include "ray.hpp"

namespace rt2
{

	class Triangle
	{
		private:
			mlib::vec4 v0, v1, v2, normal;

		public:
			Triangle(mlib::vec4 a, mlib::vec4 b, mlib::vec4 c, mlib::vec4 n);
			Triangle(const Triangle & t);

			float crossing(Ray & r, mlib::vec4 & point);
			mlib::vec4 get_normal();

	};


}

#endif

