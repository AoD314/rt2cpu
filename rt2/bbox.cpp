
#include "bbox.hpp"

#include <mlib/minmax.hpp>
#include <mlib/float.hpp>
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
                bmin.set1(Float::MaxValue());
                bmax.set1(Float::MinValue());

                for (size_t i = 0; i < mesh.size(); i++)
                {
                        vec4 a,b,c;
                        mesh[i].get_points(a,b,c);
                        if (bmax < a) bmax = a;
                        if (bmax < b) bmax = b;
                        if (bmax < c) bmax = c;

                        if (bmin > a) bmin = a;
                        if (bmin > b) bmin = b;
                        if (bmin > c) bmin = c;
                }
        }

        bool BBox::in(Triangle & t)
        {
                vec4 a,b,c;
                t.get_points(a,b,c);
                return is_cross(Ray(a, normalize(b-a))) || is_cross(Ray(b, normalize(c-b))) || is_cross(Ray(c, normalize(a-c)));
        }

        vec4 BBox::get_split_point(Split_point point)
        {
                vec4 bv_size = abs(bmax - bmin);

                int os = 0;
                float max = bv_size[0];

                if ( bv_size[1] > max)
                {
                        max = bv_size[1];
                        os = 1;
                }

                if ( bv_size[2] > max)
                {
                        max = bv_size[2];
                        os = 2;
                }

                max /= 2.0f;

                bv_size(os, max);

                if (point == split_min)
                {
                        return vec4(bmin + bv_size);
                }
                else if (point == split_max)
                {
                        vec4 lmax(0.0f);
                        lmax(os, max);
                        return vec4(bmin + lmax);
                }
        }

        vec4 BBox::get_max_point()
        {
                return bmax;
        }

        vec4 BBox::get_min_point()
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

