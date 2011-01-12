
#include "pr_plane.hpp"

namespace primitives
{
        Plane::Plane ( vec4& _p, vec4& _d )
        {
                orientation = normalize(_d - _p);

                position = _p;

                D = -dot ( position, orientation );

                //position[3] = -_d[0]*_p[0] + _d[1]*_p[1] - _d[2]*_p[2];
        }

        vec4 Plane::CalcNormal ( vec4& tp )
        {
                return orientation;
        }

        bool Plane::isCrossing ( Ray& r )
        {
                return false;
        }

        void Plane::Move ( vec4& v )
        {
                position = v;

                D = -dot ( position, orientation );
        }

        void Plane::MoveN ( vec4& v )
        {
                orientation = normalize(v - position);

                D = -dot ( position, orientation );
        }

        float Plane::Crossing ( Ray& r, vec4& tp )
        {
                //cout << "[plane]";

                float tmp1, tmp2, tr;
                tr = -1;

                tmp1 = dot ( orientation, r.Direction ( ) );

                tmp2 = dot ( orientation, r.Position ( ) ) ;

                tmp2 -= D;

                if ( tmp1 != 0.0f )
                {
                        tr = -tmp2 / tmp1;


                        if ( tr >= 0.0f )
                        {
                                tp = tr * r.Direction ( ) + r.Position ( );
                        }
                }

                return tr;
        }

}

