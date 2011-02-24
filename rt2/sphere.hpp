
#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__

#include <mlib/fixed_vector.hpp>

#include "primitive.hpp"
#include "ray.hpp"

namespace rt2
{

        class Sphere : public Primitive
	{
		private:
			mlib::vec4 pos;
			float rad;

		public:
			Sphere(mlib::vec4 position, float radius);
                        Sphere(const Sphere & s);
                        void operator = (const Sphere & s);

                        float crossing(const Ray & r);
                        mlib::vec4 get_normal(const mlib::vec4 & point) const;
                        BBox get_bbox();

	};
}

#endif
