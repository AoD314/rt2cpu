
#ifndef __pr_plane_hpp__
#define __pr_plane_hpp__

#include "primitives.hpp"

namespace primitives
{
        class Plane : public Primitives
        {
                private:
                        float D;

                public:
                        Plane(vec4& _p, vec4& _d);

                        float Crossing (Ray& r, vec4& tp);

                        void Move(vec4& v);

                        void MoveN(vec4& v);

                        bool isCrossing (Ray& r);

                        inline vec4 CalcNormal (vec4& tp);
        };

}

#endif

