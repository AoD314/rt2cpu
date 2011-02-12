
#ifndef __BBOX_HPP__
#define __BBOX_HPP__

#include <vector>

#include "ray.hpp"
#include "triangle.hpp"

#include <mlib/fixed_vector.hpp>

namespace rt2
{
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
			BBox ( mlib::vec4 mn, mlib::vec4 mx);
                        BBox (std::vector<Triangle> mesh);

                        bool is_cross(const Ray & r);
                        bool in(const Triangle & t);

                        mlib::vec4 get_split_point(Split_point point);
                        mlib::vec4 get_max_point();
                        mlib::vec4 get_min_point();
	};
}

#endif

