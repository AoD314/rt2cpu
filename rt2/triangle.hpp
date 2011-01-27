
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
			mlib::vec4 e1, e2;

		public:
			Triangle();
			Triangle(mlib::vec4 a, mlib::vec4 b, mlib::vec4 c, mlib::vec4 n);
			Triangle(const Triangle & t);

			float get_crossing_point(Ray & r, mlib::vec4 & point);
			bool is_cross(Ray & r);

			mlib::vec4 get_normal();
	};


}

#endif

