
#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__

#include "config.hpp"

#ifdef use_tbb

        #include <tbb/task_scheduler_init.h>
        #include <tbb/parallel_for.h>
        #include <tbb/blocked_range.h>

#endif

#include "scene.hpp"

#include <mlib/timer.hpp>

namespace rt2
{
	class Engine
	{
		private:
			unsigned int * vbuf;
                        Scene * scene;

                        size_t threads;
                        size_t depth;
                        size_t grainsize;

			unsigned long long num_frame;
			float fps;
                        mlib::Timer timer;

                        #ifdef use_tbb

                                //tbb::task_scheduler_init init;
                                //tbb::affinity_partitioner ap;

                        #endif

                        inline mlib::vec4 reflect(const mlib::vec4 & n, const mlib::vec4 & i);
                        mlib::vec4 ray_tracing(const Ray & ray, size_t d);

		public:
                        Engine(Scene * s, unsigned int * vbuffer);
			void rendering();

			unsigned long long get_num_frame();

                        float  get_fps();
                        size_t get_threads();

                        void set_threads(size_t t);
                        void set_depth(size_t d);
                        void set_grainsize(size_t g);

                        ~Engine();
	};

}

#endif
