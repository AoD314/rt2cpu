
#include "pr_sphere.hpp"

namespace primitives
{

        Sphere::Sphere ( float x, float y, float z, float r )
        {
                position.set ( x, y, z, 0.0f );
                rad = r;
                r2 = r * r;
        }

        inline vec4 Sphere::CalcNormal ( vec4& tp )
        {
                return normalize(tp - position);
        }

        bool Sphere::isCrossing ( Ray& r )
        {
                bool f = false;

                float dist;

                dist = calc_distance ( r.Position ( ), position );

                float t = sqrt ( 1 - r2 / (dist * dist) );

                float sk = dot ( normalize ( r.Position ( ) - position), r.Direction ( ) );

                if ( sk < t ) f = true;

                return f;
        }

        inline float Sphere::Crossing ( Ray& r, vec4& tp )
        {
                float A, B, D, t1, t2, tr;
                tr = -1;

                A = dot ( r.Direction ( ), r.Direction ( ) );

                B = dot ( vec4(2.0f) * r.Direction () , r.Position ( ) - position );

                D = B * B - 4 * A * (dot ( r.Position ( ) - position, r.Position ( ) - position ) - r2);

                if ( D >= 0 )
                {
                        t1 =  (sqrt (D) - B) / ( 2.0f * A);
                        t2 = -(sqrt (D) + B) / ( 2.0f * A);

                        if ( t1 >= 0 )
                                if ( t2 >= 0 )
                                        tr = min ( t1, t2 );
                                else
                                        tr = t1;
                        else
                                if ( t2 >= 0 )
                                tr = t2;
                        else
                                tr = -1;
                }

                if ( tr > 0 )
                {
                        tp = (r.Direction ( ) * tr) + r.Position ( );
                }

                return tr;
        }

}

