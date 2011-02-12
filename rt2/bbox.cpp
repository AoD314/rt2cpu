
#include "bbox.hpp"
#include <mlib/minmax.hpp>
using namespace mlib;

namespace rt2
{

	BBox::BBox(vec4 mn, vec4 mx)
	{
		bmin = mn;
		bmax = mx;
	}

        BBox::BBox(std::vector<Triangle> mesh)
        {

        }

        bool BBox::in(const Triangle & t)
        {
                return false;
        }

        mlib::vec4 BBox::get_split_point(Split_point point)
        {
                vec4 p;

                if (point == split_min)
                {

                }
                else if (point == split_max)
                {

                }

                return p;
        }

        mlib::vec4 BBox::get_max_point()
        {
                return bmax;
        }

        mlib::vec4 BBox::get_min_point()
        {
                return bmin;
        }

        bool BBox::is_cross(const Ray & r)
	{
		vec4 tmin = (bmin - r.pos()) / r.dir();
		vec4 tmax = (bmax - r.pos()) / r.dir();

		vec4 rmin = min(tmin, tmax);
		vec4 rmax = max(tmin, tmax);

		float mmax = min( min( rmax[0], rmax[1]), rmax[2]);
		float mmin = max( max( rmin[0], rmin[1]), rmin[2]);
		
                return (mmax >= mmin && mmax >= 0.0f);
	}

}

