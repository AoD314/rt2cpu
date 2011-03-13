
#include "camera.hpp"

using namespace mlib;

const float PI = 3.1415926535897932384626433832795f;
const float rad_to_angle = PI / 180.0f;

#include "config.hpp"

namespace rt2
{
	Camera::Camera()
	{
		pos    = vec4(5.0f, 0.0f, 0.0f, 0.0f);
		dir    = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
		dir_up = vec4(0.0f, 1.0f, 0.0f, 0.0f);
		dir_lf = normalize ( cross ( dir, dir_up ));
		width  = 512;
		height = 512;
		aspect = static_cast<float>(width) / static_cast<float>(height);
                tan_aview = tan (60.0f * rad_to_angle);

                aa = 1;
                dX = new float[aa];
                dY = new float[aa];
                dX[0] = 0.0f;
                dY[0] = 0.0f;
	}

        void Camera::operator = (const Camera & cam)
        {
                pos       = cam.pos;
                dir       = cam.dir;
                dir_up    = cam.dir_up;
                dir_lf    = cam.dir_lf;
                width     = cam.width;
                height    = cam.height;
                aspect    = cam.aspect;
                tan_aview = cam.tan_aview;
                aa        = cam.aa;

                dX = new float[aa];
                dY = new float[aa];
                for (unsigned int i = 0; i < aa; i++)
                {
                        dX[i] = cam.dX[i];
                        dY[i] = cam.dY[i];
                }
        }

        Camera::Camera(vec4 p, vec4 d, vec4 du, unsigned int w, unsigned int h, float angleofview, unsigned int aa)
	{
		pos = p;
		dir = d;
		dir_up = du;
		dir_lf = normalize ( cross ( dir, dir_up ));
		width = w;
		height = h;
		aspect = static_cast<float>(width) / static_cast<float>(height);
                tan_aview = tan (angleofview * rad_to_angle);

                this->aa = aa;
                dX = new float[aa];
                dY = new float[aa];
                if (aa > 1)
                {
                        for (unsigned int i = 0; i < aa; i++)
                        {
                                dX[i] =  1.0f / static_cast<float>(width)  * (1 - cos(2.0f * PI / static_cast<float>(aa) * static_cast<float>(i)));
                                dY[i] = -1.0f / static_cast<float>(height) * (1 - sin(2.0f * PI / static_cast<float>(aa) * static_cast<float>(i)));
                        }
                }
                else
                {
                        dX[0] = 0.0f;
                        dY[0] = 0.0f;
                }
	}

	Camera::Camera(const Camera & cam)
	{
		pos       = cam.pos;
		dir       = cam.dir;
		dir_up    = cam.dir_up;
		dir_lf    = cam.dir_lf;
		width     = cam.width;
		height    = cam.height;
		aspect    = cam.aspect;
		tan_aview = cam.tan_aview;
                aa        = cam.aa;

                dX = new float[aa];
                dY = new float[aa];
                for (unsigned int i = 0; i < aa; i++)
                {
                        dX[i] = cam.dX[i];
                        dY[i] = cam.dY[i];
                }
	}

	unsigned int Camera::get_width()
	{
		return width;
	}

	unsigned int Camera::get_height()
	{
		return height;
	}

        unsigned int Camera::get_aa()
        {
                return aa;
        }


        Ray Camera::get_ray(unsigned int i, unsigned int j, unsigned int part)
	{
		float xx = 2.0f * (static_cast<float>(i) / static_cast<float>(width) ) - 1.0f;
		float yy = 1.0f - 2.0f * (static_cast<float>(j) / static_cast<float>(height) );

                #ifdef new_alg_aa

                        xx += dX[part];
                        yy += dY[part];

                #else

                        if (aa > 1)
                        {
                                float deltaX =   2.0f / static_cast<float>(width  * (aa - 1));
                                float deltaY = - 2.0f / static_cast<float>(height * (aa - 1));

                                xx += deltaX * static_cast<float>(part % aa);
                                yy += deltaY * static_cast<float>(part / aa);
                        }

                #endif

		xx *= (aspect * tan_aview);
		yy *= tan_aview;

                vec4 direction = normalize(dir + dir_lf * xx + dir_up * yy);

		return Ray(pos, direction);
	}

        Camera::~Camera()
        {
                delete [] dX;
                delete [] dY;
        }

}

