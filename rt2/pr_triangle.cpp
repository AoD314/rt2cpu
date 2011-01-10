
#include "pr_triangle.hpp"

namespace primitives
{
        Triangle::Triangle()
        {
                V0.zero ();
                V1.zero ();
                V2.zero ();
                normal.zero ();
        }

        vec4 Triangle::GetMin()
        {
                vec4 min = Min (V0, V1);
                min = Min (min, V2);
                return min;
        }

        vec4 Triangle::GetMax()
        {
                vec4 min = Max (V0, V1);
                min = Max (min, V2);
                return min;
        }

        Triangle::Triangle ( vec4& V0_d, vec4& V1_d, vec4& V2_d )
        {
                V0 = V0_d;
                V1 = V1_d;
                V2 = V2_d;
        }

        Triangle::Triangle( const Triangle & tr)
        {
                V0 = tr.V0;
                V1 = tr.V1;
                V2 = tr.V2;
        }

        vec4 Triangle::CalcNormal ( vec4& tp )
        {
                return normal;
        }

        void Triangle::SetCoordinate(vec4& V0_d, vec4& V1_d, vec4& V2_d)
        {
                V0 = V0_d;
                V1 = V1_d;
                V2 = V2_d;
        }

        void Triangle::SetNormal(vec4 norm)
        {
                normal = norm;
        }

        float Triangle::Crossing ( Ray& r, vec4& tp )
        {
                vec4 E1 = V1 - V0;
                vec4 E2 = V2 - V0;
                vec4 T = r.Position ( ) - V0;
                vec4 Q = Cross ( T, E1 );
                vec4 P = Cross ( r.Direction ( ), E2 );

                float temp = 1 / ( dot ( P, E1 ) );

                vec4 tuv;
                vec4 tmp(
                                        dot(Q,E2),
                                        dot(P,T),
                                        dot(Q,r.Direction ()),
                                        0.0f
                                );

                tuv = temp * tmp;

                if (tuv[0] >= 0 && tuv[1] >= 0 && tuv[2] >= 0 && (tuv[1] + tuv[2] <= 1) )
                        tp = r.Position ( ) + tuv[0] * r.Direction ();
                else
                        tuv.set(-1.0f, 0.0f, 0.0f, 0.0f);

                //std::cout << "\n[" << u << "][" << v << "][" << tr << "][" << tp << "]";

                return tuv[0];
        }

}
