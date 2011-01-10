
#ifndef __lights_hpp__
#define __lights_hpp__

#include "smath.hpp"

#include "ray.hpp"

using namespace ray;

#include <mlib/fixed_vector.hpp>
using namespace mlib;

namespace light
{

        class Lights
        {
        protected:
                vec4 Ia;
                vec4 Is;
                vec4 Id;

                size_t status;

                vec4 pos;

        public:
                Lights(vec4& Pos, vec4 &Ia, vec4 &Is, vec4 &Id);

                Lights();

                void On();

                void Off();

                void Move(vec4& npos);

                vec4 & GetColor_Ia();
                vec4 & GetColor_Is();
                vec4 & GetColor_Id();

                vec4& Position();

                void settings(vec4& Pos, vec4 &Ia, vec4 &Is, vec4 &Id);
        };


        class PointLight : public Lights
        {
        public:
                PointLight(vec4& Pos, vec4& ia, vec4& is, vec4& id);

                PointLight();

        };

}

#endif

