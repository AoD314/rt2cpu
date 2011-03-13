
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
                        unsigned int aa;
			float aspect, tan_aview;

                        float * dX;
                        float * dY;
		public:
			Camera();
                        Camera(mlib::vec4 p, mlib::vec4 d, mlib::vec4 du, unsigned int w, unsigned int h, float angleofview, unsigned int aa = 1);
			Camera(const Camera & cam);
                        void operator = (const Camera & cam);

                        Ray get_ray(unsigned int i, unsigned int j, unsigned int part = 0);

			unsigned int get_width();
			unsigned int get_height();
                        unsigned int get_aa();

                        ~Camera();
	};

}

#endif

