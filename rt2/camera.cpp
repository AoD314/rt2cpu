
#include "camera.hpp"

namespace camera
{

        Camera::Camera ( ) { }

        Camera::Camera ( vec4& pos, vec4& dir, vec4& updir, size_t w, size_t h, float aview )
        {
                position = pos;
                direction = normalize(dir - pos);

                updirection = normalize(updir - pos);

                leftdirection = normalize ( cross ( direction, updirection ));

                width = w;
                height = h;
                aspect =  static_cast<float>(w) / static_cast<float>(h);
                angleofview = aview;
        }

        size_t Camera::GetWidth ( )
        {
                return width;
        }

        size_t Camera::GetHeight ( )
        {
                return height;
        }

        void Camera::Move ( vec4& v )
        {
                position = v;
        }

        Ray Camera::GenerateRay ( int i, int j, int part, int allpart)
        {
                /*
                float xx = 2 *     (( float ) i / width ) - 1;  // -1 <= xx <= 1
                float yy = 1 - 2 * (( float ) j / height);      // -1 <= yy <= 1

                //std::cout << std::endl << "(i,j) = (" << i << "," << j << ") = "<< part << " from " << allpart ; std::cout << "(xx,yy) = (" << xx << "," << yy << ")";

                float sdvig = 2.0f/ (float)(allpart * width);

                xx += (sdvig*(part % allpart));
                yy += (sdvig*(part / allpart));

                //std::cout << " (nxx,nyy) = (" << xx << "," << yy << ")";

                float tmp = tan ( angleofview );
                xx *= (aspect * tmp);
                yy *= tmp;

                */

                float xx = 2 *     (static_cast<float>(i) / static_cast<float>(width ) ) - 1;  // -1 <= xx <= 1
                float yy = 1 - 2 * (static_cast<float>(j) / static_cast<float>(height) ) ;     // -1 <= yy <= 1

                float sdvigX =   2.0f / width ;
                float sdvigY = - 2.0f / height;

                if (allpart > 1)
                {
                        sdvigX /= static_cast<float>(allpart - 1);
                        sdvigY /= static_cast<float>(allpart - 1);
                }

                xx += sdvigX * (part % allpart);
                yy += sdvigY * (part / allpart);

                float tanAngl = tan ( angleofview );
                xx *= (aspect * tanAngl);
                yy *= tanAngl;

                vec4 temp = direction + leftdirection * xx + updirection*yy;
                temp.normalize ();

                Ray r ( position, temp );

                return r;
        }
}

