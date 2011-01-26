
#include "engine.hpp"

namespace rt2
{
	Engine::Engine(Scene s, unsigned int * vbuffer)
	{
		scene = s;
		num_frame = 0;
	}

	void Engine::rendering()
	{
		timer.Start();

		//rendering

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