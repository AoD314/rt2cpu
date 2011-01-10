
#ifndef __engine_hpp__
#define __engine_hpp__

#ifdef _TBB_

        #include <tbb/task_scheduler_init.h>
        #include <tbb/parallel_for.h>
        #include <tbb/blocked_range.h>

        using namespace tbb;

#endif

#include <math.h>
#include <omp.h>

#include "scene.hpp"
#include "all_obj.hpp"


#include <mlib/timer.hpp>
#include <mlib/minmax.hpp>
#include <mlib/fixed_vector.hpp>

using namespace mlib;
using namespace scene;
using namespace primitives;

namespace engine
{
        const float pi = 3.14159265358979323846264338327950288419716939937510;

        class Engine
        {
                protected:
                        Scene sc;

                        unsigned int * vbuf;

                        int width;

                        int height;

                        size_t mintimer;

                        size_t timer;

                        size_t alltimer;

                        size_t frame;

                public:
                        Engine (Scene& s, unsigned int * vbuffer);

                        size_t CountFrame();

                        size_t CountTime();

                        size_t AllTime();

                        size_t MinTime();

                        virtual void Rendering(int p = 1) = 0;
        };

        class EngineRT2 : public Engine
        {
                private:
                        int depth;

                        int parts;

                        int threads;

                        bool use_bvh;

                        Primitives* RayTrace(Ray& r, vec4& color, int depth);

                        vec4 Reflect(vec4& d, vec4& n);

                #ifdef __TBB__
                      task_scheduler_init init;
                #endif

                public:
                        EngineRT2(Scene& s, unsigned int * vbuffer, bool use_bvh = false);

                        void Rendering(int t);

                        // Gets params

                        int GetParts  ();
                        int GetThreads();
                        int GetDepth  ();

                        // Sets params

                        void SetParts  (int p);
                        void SetThreads(int p);
                        void SetDepth  (int d);

        };

}

#endif

