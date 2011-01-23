
#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "scene.cpp"

namespace rt2
{
	class Engine
	{
		private:
			unsigned int * vbuf;

			int threads;
			int aa;
			unsigned long long num_frame;


		public:
			Engine(Scene& s, unsigned int * vbuffer);
			void rendering();

			unsigned long long get_num_frame();

			int get_threads();
			int get_antialiasing();

			void set_threads(int t);
			void set_antialiasing(int a);

	};

}

#endif
