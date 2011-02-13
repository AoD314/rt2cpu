
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
                bmin.set1( Float::MaxValue());
                bmax.set1(-Float::MaxValue());

                for (size_t j = 0; j < mesh.size(); j++)
                {
                        vec4 a,b,c;
                        mesh[j].get_points(a,b,c);

                        for (int i = 0; i < 4; i++)
                        {
                                if (bmax[i] < a[i]) bmax(i, a[i]);
                                if (bmax[i] < b[i]) bmax(i, b[i]);
                                if (bmax[i] < c[i]) bmax(i, c[i]);

                                if (bmin[i] > a[i]) bmin(i, a[i]);
                                if (bmin[i] > b[i]) bmin(i, b[i]);
                                if (bmin[i] > c[i]) bmin(i, c[i]);
                        }
                }
        }

        BBox::BBox(Triangle & t)
        {
                vec4 a,b,c;
                t.get_points(a,b,c);

                bmin = vec4( Float::MaxValue());
                bmax = vec4(-Float::MaxValue());

                for (int i = 0; i < 4; i++)
                {
                        if (bmax[i] < a[i]) bmax(i, a[i]);
                        if (bmax[i] < b[i]) bmax(i, b[i]);
                        if (bmax[i] < c[i]) bmax(i, c[i]);

                        if (bmin[i] > a[i]) bmin(i, a[i]);
                        if (bmin[i] > b[i]) bmin(i, b[i]);
                        if (bmin[i] > c[i]) bmin(i, c[i]);
                }
        }

        bool BBox::in(Triangle & t)
        {
                BBox box(t);
                return (box.bmin >= (bmin - (box.bmax - box.bmin))) && box.bmin <= bmax;
        }

        vec4 BBox::get_split_point(Split_point point)
        {
                vec4 bv_size = bmax - bmin;

                int os = 0;
                float max = bv_size[0];

                if ( abs(bv_size[1]) > max)
                {
                        max = bv_size[1];
                        os = 1;
                }

                if ( abs(bv_size[2]) > max)
                {
                        max = bv_size[2];
                        os = 2;
                }

                max /= 2.0f;

                bv_size(os, max);

                if (point == split_max)
                {
                        return vec4(bmin + bv_size);
                }
                else if (point == split_min)
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

