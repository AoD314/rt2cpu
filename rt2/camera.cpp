
#include "camera.hpp"

using namespace mlib;

const float rad_to_angle = 3.1415926535897932384626433832795f / 180.0f;

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
	}

	Camera::Camera(vec4 p, vec4 d, vec4 du, unsigned int w, unsigned int h, float angleofview)
	{
		pos = p;
		dir = d;
		dir_up = du;
		dir_lf = normalize ( cross ( dir, dir_up ));
		width = w;
		height = h;
		aspect = static_cast<float>(width) / static_cast<float>(height);
                tan_aview = tan (angleofview * rad_to_angle);
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
	}

	unsigned int Camera::get_width()
	{
		return width;
	}

	unsigned int Camera::get_height()
	{
		return height;
	}

	Ray Camera::get_ray(unsigned int i, unsigned int j, unsigned int part, unsigned int allpart)
	{
		float xx = 2.0f * (static_cast<float>(i) / static_cast<float>(width) ) - 1.0f;
		float yy = 1.0f - 2.0f * (static_cast<float>(j) / static_cast<float>(height) );

		if (allpart > 1)
		{
                        float deltaX =   2.0f / static_cast<float>(width  * (allpart - 1));
                        float deltaY = - 2.0f / static_cast<float>(height * (allpart - 1));

                        xx += deltaX * static_cast<float>(part % allpart);
                        yy += deltaY * static_cast<float>(part / allpart);
		}

		xx *= (aspect * tan_aview);
		yy *= tan_aview;

                vec4 direction = normalize(dir + dir_lf * xx + dir_up * yy);

		return Ray(pos, direction);
	}

}

