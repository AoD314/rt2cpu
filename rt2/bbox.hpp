
#ifndef __BBOX_HPP__
#define __BBOX_HPP__

#include <vector>

#include <mlib/fixed_vector.hpp>

#include "ray.hpp"

#include "primitive.hpp"

namespace rt2
{
        class Primitive;

        enum Split_point
        {
                split_min,
                split_max
        };

        class BBox
	{
		private:
			mlib::vec4 bmin, bmax;

		public:
                        BBox (mlib::vec4 mn, mlib::vec4 mx);
                        BBox (std::vector<Primitive*> mesh);
                        BBox (const BBox & bbox);
                        void operator = (const BBox & bbox);

                        bool is_cross(const Ray & r);
                        bool in(Primitive * p);

                        mlib::vec4 get_split_point(Split_point point);
                        mlib::vec4 get_max_point();
                        mlib::vec4 get_min_point();
	};
}

#endif

