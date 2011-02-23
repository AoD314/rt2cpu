
#include "engine.hpp"
#include <omp.h>

#include <mlib/fixed_vector.hpp>
using namespace mlib;

#include <math.h>

namespace rt2
{
	Engine::Engine(Scene s, unsigned int * vbuffer)
	{
		scene = s;
		vbuf = vbuffer;
		num_frame = 0;
	}

	vec4 Engine::ray_tracing(Ray ray)
	{
                vec4 point;
                float t;
                Triangle * obj = scene.crossing(ray, t);

                if (obj != NULL)
                {
                        //return vec4(1.0f);
                        point = ray.pos() + t * ray.dir();

                        vec4 l_pos(4.0f, 5.0f, -4.0f, 0.0f);

                        float d = dot(normalize(obj->get_normal(point)), normalize( l_pos - point ));

                        vec4 cc;// = d * vec4(1.0f);

                        //*/
                        if (d <= 0.0f)
                        {
                                cc = vec4(0.0f, 0.0f, 1.0f, 0.0f);
                        }

                        if (d > 0.0f && d <= 1.0f)
                        {
                                cc = d * vec4(1.0f, 0.0f, 0.0f, 0.0f);
                        }

                        if (d > 1.0f)
                        {
                                cc = vec4(0.0f, 1.0f, 0.0f, 0.0f);
                        }
                        //*/

                        /*
                        vec4 r = ray.dir() - 2.0f * normal * dot(normal, ray.dir());
                        float tt = dot(r, normalize(ray.pos() - point));
                        vec4 spec;
                        if (tt >=0 )
                        {
                                spec = vec4(0.9f) * powf(tt, 32.0f);
                        }
                        */

                        return cc; // + vec4(0.05f, 0.05f, 0.05f, 0.0f); //+ spec;
                }

                return vec4(0.0f);
	}

	void Engine::rendering()
	{
		timer.Start();

		unsigned int w = scene.get_cam().get_width();
		unsigned int h = scene.get_cam().get_height();

                unsigned int i, j, s;
		Camera cam = scene.get_cam();

                omp_set_num_threads(threads);

                #pragma omp parallel for private(i, j, s) schedule(static, 1)
                for (j = 0; j < h; j++)
                        for (i = 0; i < w; i++)
			{
                                vec4 color_total;
                                for (s = 0; s < aa; s++)
                                {
                                        color_total += ray_tracing(cam.get_ray(i, j, s, aa));
                                }
                                vbuf[j*w +i] = to_color(color_total / static_cast<float>(aa));
			}

		timer.Stop();
		fps = static_cast<float>(timer.OperationPerSecond());
		num_frame++;
	}

	unsigned long long Engine::get_num_frame()
	{
		return num_frame;
	}

	int Engine::get_threads()
	{
		return threads;
	}

	int Engine::get_antialiasing()
	{
                return static_cast<int>(sqrt(aa));
	}

	void Engine::set_threads(int t)
	{
		threads = t;
	}

	void Engine::set_antialiasing(int a)
	{
                aa = a * a;
	}

	void Engine::set_depth(int d)
	{
		depth = d;
	}

	float Engine::get_fps()
	{
		return fps;
	}

}
