
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
                        Scene * scene;

			int threads;
			int depth;

			unsigned long long num_frame;
			float fps;
                        //mlib::Timer timer;

                        mlib::vec4 reflect(mlib::vec4 n, mlib::vec4 i);
                        mlib::vec4 ray_tracing(const Ray & ray, int d);

		public:
                        Engine(Scene * s, unsigned int * vbuffer);
			void rendering();

			unsigned long long get_num_frame();

			float get_fps();
			int get_threads();

			void set_threads(int t);
			void set_depth(int d);

	};

}

#endif
