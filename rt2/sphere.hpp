
#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include <mlib/fixed_vector.hpp>

#include "ray.hpp"

namespace rt2
{

	class Sphere
	{
		private:
			mlib::vec4 pos;
			float rad;

		public:
			Sphere(mlib::vec4 position, float radius);
                        Sphere(const Sphere & s);

                        void operator = (const Sphere & s);

                        float get_crossing_point(const Ray & r, mlib::vec4 & point);
                        bool is_cross(const Ray & r);

			mlib::vec4 get_normal(const mlib::vec4 & point);

	};
}

#endif
