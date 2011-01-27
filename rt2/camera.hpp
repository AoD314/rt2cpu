
#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "ray.hpp"

#include <mlib/fixed_vector.hpp>

namespace rt2
{
	class Camera
	{
		private:
			mlib::vec4 pos, dir, dir_up, dir_lf;
			unsigned int width, height;
			float aspect, tan_aview;

		public:
			Camera();
			Camera(mlib::vec4 p, mlib::vec4 d, mlib::vec4 du, unsigned int w, unsigned int h, float angleofview );
			Camera(const Camera & cam);

			Ray get_ray(unsigned int i, unsigned int j, unsigned int part = 1, unsigned int allpart = 1);

			unsigned int get_width();
			unsigned int get_height();

	};

}

#endif

