
#include "engine.hpp"
#include <omp.h>

#include <mlib/fixed_vector.hpp>
using namespace mlib;

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
		Sphere * t = scene.crossing(ray);
		if ( t == NULL)
			return vec4(0.0f);
		else
			return vec4(1.0f, 1.0f, 1.0f, 0.0f);
	}

	void Engine::rendering()
	{
		timer.Start();

		unsigned int w = scene.get_cam().get_width();
		unsigned int h = scene.get_cam().get_height();

		unsigned int i, j;
		vec4 color;
		Camera cam = scene.get_cam();

                omp_set_num_threads(threads);

		#pragma omp parallel for private(i, j, color) schedule(static, 1)
		for (j = 0; j < h; j++)
			for (i = 0; i < w; i++)
			{
				color = ray_tracing(cam.get_ray(i,j));
				vbuf[j*w +i] = to_color(color);
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
		return aa;
	}

	void Engine::set_threads(int t)
	{
		threads = t;
	}

	void Engine::set_antialiasing(int a)
	{
		aa = a;
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
