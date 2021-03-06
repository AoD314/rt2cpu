
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

        BBox::BBox(const BBox & bbox)
        {
                bmin = bbox.bmin;
                bmax = bbox.bmax;
        }

        BBox::BBox(std::vector< rt2::Primitive * > mesh)
        {
                bmax.set1(-Float::MaxValue());
                bmin.set1( Float::MaxValue());

                for (size_t j = 0; j < mesh.size(); j++)
                {
                        BBox local_box = mesh[j]->get_bbox();
                        bmax = max(bmax, local_box.get_max_point());
                        bmin = min(bmin, local_box.get_min_point());
                }
        }

        void BBox::operator = (const BBox & bbox)
        {
                bmax = bbox.bmax;
                bmin = bbox.bmin;
        }

        bool BBox::in(rt2::Primitive * p)
        {                
                BBox box = p->get_bbox();
                return ((box.bmax >= bmin) && (box.bmin <= bmax));
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
