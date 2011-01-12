
#include "pr_mesh.hpp"
#include "pr_triangle.hpp"

namespace primitives
{
        Mesh::Mesh (std::size_t size)
        {
            points = new List<vec4>(size);
            count = 0;
        }

        void Mesh::AddVec4(vec4 & v)
        {
            points->Add (v);
            count++;
        }

        Mesh::~Mesh()
        {
            delete(points);
        }

        float Mesh::Crossing (Ray& r, vec4& tp)
        {
            float d = std::numeric_limits<float>::max ();
            vec4 ret_vec;

            for (size_t i = 0; i < (count / 3); i++)
            {
                vec4 v0 = points->Get(i*3 + 0);
                vec4 v1 = points->Get(i*3 + 1);
                vec4 v2 = points->Get(i*3 + 2);

                Triangle t(v0, v1, v2);
                float tmp = t.Crossing (r, tp);

                if ( tmp > 0 )
                        if ( tmp < d )
                        {
                                d = tmp;
                                ret_vec = tp;
                        }

            }

            tp = ret_vec;
            return d;
        }

        inline vec4 Mesh::CalcNormal (vec4& tp)
        {
                float D = std::numeric_limits<float>::max ();

                std::size_t ipos = 0;
                vec4 v0;
                vec4 v1;
                vec4 v2;

                for (size_t i = 0; i < (count / 3); i++)
                {
                        vec4 v0 = points->Get(i*3 + 0);
                        vec4 v1 = points->Get(i*3 + 1);
                        vec4 v2 = points->Get(i*3 + 2);

                        float d = calc_distance (v0, tp) + calc_distance (v1, tp) + calc_distance (v2, tp);
                        if (d < D)
                        {
                                ipos = i;
                                D = d;
                        }
                }

                v0 = points->Get (ipos * 3 + 0);
                v1 = points->Get (ipos * 3 + 1);
                v2 = points->Get (ipos * 3 + 2);

                return cross ( v1 - v0, v1 - v2 );
        }

}

