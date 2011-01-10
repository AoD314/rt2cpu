
#ifndef __camera_hpp__
#define __camera_hpp__

#include "smath.hpp"

#include "ray.hpp"
using namespace ray;

#include <mlib/fixed_vector.hpp>
using namespace mlib;


namespace camera
{

        class Camera
        {
                private:
                        vec4 position;

                        vec4 direction;

                        vec4 updirection;

                        vec4 leftdirection;

                        int width;

                        int height;

                        float aspect;

                        float angleofview;

                public:
                        Camera();

                        Camera(vec4& pos, vec4& dir, vec4& updir, size_t w, size_t h, float aview);

                        Ray GenerateRay(int i, int j, int part, int allpart);

                        size_t GetWidth ();

                        size_t GetHeight ();

                        void Move(vec4& v);
        };

}

#endif

