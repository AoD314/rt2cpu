
#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "scene.hpp"

#include <mlib/timer.hpp>

namespace rt2
{
	class Engine
	{
		private:
			unsigned int * vbuf;
			Scene scene;

			int threads;
			int aa;
			int depth;

			unsigned long long num_frame;
			float fps;
			mlib::Timer timer;

			mlib::vec4 ray_tracing(Ray ray);

		public:
			Engine(Scene s, unsigned int * vbuffer);
			void rendering();

			unsigned long long get_num_frame();

			float get_fps();
			int get_threads();
			int get_antialiasing();


			void set_threads(int t);
			void set_depth(int d);
			void set_antialiasing(int a);

	};

}

#endif