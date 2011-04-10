
#ifndef __TRIANGLE_HPP__
#define __TRIANGLE_HPP__

#include <mlib/fixed_vector.hpp>

#include "primitive.hpp"
#include "ray.hpp"

namespace rt2
{

        class Triangle : public Primitive
	{
		private:
                        mlib::vec4 v0, e1, e2, normal, v1, v2;

		public:
                        Triangle(mlib::vec4 a, mlib::vec4 b, mlib::vec4 c);
			Triangle(const Triangle & t);
                        void operator = (const Triangle & t);

                        mlib::vec4 get_normal(const mlib::vec4 & point)const;
                        float crossing(const Ray & r);
                        BBox get_bbox();
	};


}

#endif

