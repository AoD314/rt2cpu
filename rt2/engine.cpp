
#include "engine.hpp"

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

	void Engine::rendering()
	{
		timer.Start();

		unsigned int w = scene.get_cam().get_width();
		unsigned int h = scene.get_cam().get_height();

		unsigned int i, j;
		vec4 color(1.0f, 0.0f, 0.0f, 0.0f);;
		Ray ray(vec4::zero(), vec4::zero());

		#pragma omp parallel for private(i, j, color) schedule(static, 2)
		for (j = 0; j < h; j++)
			for (i = 0; i < w; i++)
			{
				scene.crossing(ray);

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

	float Engine::get_fps()
	{
		return fps;
	}

}
