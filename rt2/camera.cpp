
#include "camera.hpp"

using namespace mlib;

const float PI = 3.1415926535897932384626433832795f;
const float angle_to_rad = PI / 180.0f;

#include "config.hpp"

namespace rt2
{
        Camera::Camera(vec4 p, float angleX, float angleY, float angleZ, unsigned int w, unsigned int h, float angleofview, unsigned int aa)
	{
                pos    = p;
                dir    = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
                dir_up = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
                dir_lf = normalize ( cross ( dir, dir_up ));

                width  = w;
		height = h;
		aspect = static_cast<float>(width) / static_cast<float>(height);
                tan_aview = tan (angleofview * angle_to_rad);

                aX = aY = aZ = 0.0f;

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

                rotate_x(angleX);
                rotate_y(angleY);
                rotate_z(angleZ);
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

        void Camera::move(vec4 npos)
        {
                pos = npos;
        }

        void Camera::rotate_x(float deg)
        {
                aX += deg * angle_to_rad;

                dir    = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
                dir_up = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
                dir_lf = normalize ( cross ( dir, dir_up ));

                vec4 mat1(1.0f,     0.0f,      0.0f, 0.0f);
                vec4 mat2(0.0f, cosf(aX), -sinf(aX), 0.0f);
                vec4 mat3(0.0f, sinf(aX),  cosf(aX), 0.0f);

                dir    = normalize(vec4( dot(mat1, dir),    dot(mat2, dir),    dot(mat3, dir),    0.0f));
                dir_lf = normalize(vec4( dot(mat1, dir_lf), dot(mat2, dir_lf), dot(mat3, dir_lf), 0.0f));
                dir_up = normalize(vec4( dot(mat1, dir_up), dot(mat2, dir_up), dot(mat3, dir_up), 0.0f));

        }

        void Camera::rotate_y(float deg)
        {
                aY += deg * angle_to_rad;

                dir    = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
                dir_up = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
                dir_lf = normalize ( cross ( dir, dir_up ));

                vec4 mat1( cosf(aY), 0.0f, sinf(aY), 0.0f);
                vec4 mat2(     0.0f, 1.0f, 0.0f,     0.0f);
                vec4 mat3(-sinf(aY), 0.0f, cosf(aY), 0.0f);

                dir    = normalize(vec4( dot(mat1, dir),    dot(mat2, dir),    dot(mat3, dir),    0.0f));
                dir_lf = normalize(vec4( dot(mat1, dir_lf), dot(mat2, dir_lf), dot(mat3, dir_lf), 0.0f));
                dir_up = normalize(vec4( dot(mat1, dir_up), dot(mat2, dir_up), dot(mat3, dir_up), 0.0f));
        }

        void Camera::rotate_z(float deg)
        {
                aZ += deg * angle_to_rad;

                dir    = vec4(-1.0f, 0.0f, 0.0f, 0.0f);
                dir_up = vec4( 0.0f, 1.0f, 0.0f, 0.0f);
                dir_lf = normalize ( cross ( dir, dir_up ));

                vec4 mat1(cosf(aZ), -sinf(aZ), 0.0f, 0.0f);
                vec4 mat2(sinf(aZ),  cosf(aZ), 0.0f, 0.0f);
                vec4 mat3(0.0f,          0.0f, 1.0f, 0.0f);

                dir    = normalize(vec4( dot(mat1, dir),    dot(mat2, dir),    dot(mat3, dir),    0.0f));
                dir_lf = normalize(vec4( dot(mat1, dir_lf), dot(mat2, dir_lf), dot(mat3, dir_lf), 0.0f));
                dir_up = normalize(vec4( dot(mat1, dir_up), dot(mat2, dir_up), dot(mat3, dir_up), 0.0f));
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

