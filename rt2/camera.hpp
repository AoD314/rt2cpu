
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

                        float aX, aY, aZ;

                        float * dX;
                        float * dY;
		public:
                        Camera(mlib::vec4 p, float angleX, float angleY, float angleZ, unsigned int w, unsigned int h, float angleofview, unsigned int aa = 1);

                        Ray get_ray(unsigned int i, unsigned int j, unsigned int part = 0);

			unsigned int get_width();
			unsigned int get_height();
                        unsigned int get_aa();

                        void move(mlib::vec4 npos);
                        void rotate_x(float deg);
                        void rotate_y(float deg);
                        void rotate_z(float deg);

                        ~Camera();
	};

}

#endif

