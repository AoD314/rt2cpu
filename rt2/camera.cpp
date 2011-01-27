
#include "camera.hpp"

using namespace mlib;

namespace rt2
{
	Camera::Camera(vec4 p, vec4 d, vec4 du, unsigned int w, unsigned int h, float angleofview)
	{
		pos = p;
		dir = d;
		dir_up = du;
		dir_lf = normalize ( cross ( dir, dir_up ));
		width = w;
		height = h;
		aspect = static_cast<float>(width) / static_cast<float>(height);
		tan_aview = tan (angleofview);
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

		float deltaX =   2.0f / width ;
		float deltaY = - 2.0f / height;

		if (allpart > 1)
		{
			deltaX /= static_cast<float>(allpart - 1);
			deltaY /= static_cast<float>(allpart - 1);

			xx += deltaX * (part % allpart);
			yy += deltaY * (part / allpart);
		}

		xx *= (aspect * tan_aview);
		yy *= tan_aview;

		vec4 direction = dir + dir_lf * xx + dir_up * yy;
		direction.normalize();

		return Ray(pos, direction);
	}

}

