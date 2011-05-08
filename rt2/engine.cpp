
#include "engine.hpp"
#include <omp.h>

#include <mlib/fixed_vector.hpp>
using namespace mlib;

#include <math.h>

namespace rt2
{
        Engine::Engine(Scene * s, unsigned int * vbuffer)
	{
		scene = s;
		vbuf = vbuffer;
		num_frame = 0;
	}

        inline vec4 Engine::reflect(const vec4 & n, const vec4 & i)
        {
                return i - 2.0f * n * dot (n, i);
        }


        vec4 Engine::ray_tracing(const Ray & ray, int depth_local)
	{
                vec4 point;
                float t;
                Primitive * obj = scene->crossing(ray, t);

                vec4 color(0.0f);

                if (obj == NULL)
                {
                        return color;
                }
                else
                {
                        vec4 rdir = ray.dir();
                        vec4 rpos = ray.pos();
                        point = rpos + t * rdir;


                        vec4 normal = obj->get_normal(point);

                        int cl = scene->get_lights();

                        vec4 ref = reflect(normal, rdir);

                        cl += scene->get_lights();

                        Light light;

                        color = vec4(0.05f, 0.05f, 0.05f, 0.0f);

                        for (int i = 0; i < cl; i++)
                        {
                                light = scene->get_light(i);
                                vec4 l_pos = light.pos();
                                vec4 l_col = light.color();
                                vec4 dir_to_l = normalize(l_pos - point);

                                Ray ray_shadow(point + dir_to_l * 0.00025f, dir_to_l);
                                Primitive * obj_shadow = scene->crossing(ray_shadow, t);

                                if (obj_shadow == NULL || calc_distance(point, l_pos) < t)
                                {
                                        float d = dot(normal, dir_to_l);
                                        if (d < 0.0f) d = 0.0f;
                                        color += l_col * d;

                                        float tt = dot(ref, normalize(rpos - point));

                                        if (tt > 0.0f)
                                        {
                                                color += vec4(0.75f) * powf(tt, 64.0f); // spec
                                        }
                                }
                        }

                        if ( depth_local > 1)
                        {
                                Ray rray(point + ref * 0.0025f, ref);
                                color += ray_tracing(rray, depth_local - 1) * 0.75f;
                        }

                        return color;
                }
	}

	void Engine::rendering()
	{
                timer.Start();

                unsigned int w = scene->get_cam()->get_width();
                unsigned int h = scene->get_cam()->get_height();

                unsigned int i, j;

                Camera * cam = scene->get_cam();
                int aa = cam->get_aa();

                #ifndef use_tbb

                        #pragma omp parallel for private(i, j) schedule(static, 1)
                        for (j = 0; j < h; j++)
                                for (i = 0; i < w; i++)
                                {
                                        vec4 color_total;
                                        for (unsigned int s = 0; s < aa; s++)
                                        {
                                                color_total += ray_tracing(cam->get_ray(i, j, s), depth);
                                        }
                                        color_total /= static_cast<float>(aa);
                                        vbuf[j * w + i] = to_color(color_total);
                                }

                #else

                        tbb::parallel_for
                        (
                                tbb::blocked_range<unsigned int> ( static_cast<unsigned int>(0), w * h ),
                                [&]( const tbb::blocked_range<unsigned int> & range)
                                {
                                        unsigned int i, j;
                                        for ( unsigned int ind = range.begin(); ind < range.end(); ind++ )
                                        {
                                                i = ind / w;
                                                j = ind - i * w;

                                                vec4 color_total;
                                                for (unsigned int s = 0; s < aa; s++)
                                                {
                                                        color_total += ray_tracing(cam->get_ray(i, j, s), depth);
                                                }
                                                color_total /= static_cast<float>(aa);
                                                vbuf[ind] = to_color(color_total);
                                        }
                                }, ap
                        );

                #endif

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

	void Engine::set_threads(int t)
	{
		threads = t;
                #ifndef use_tbb
                        omp_set_num_threads(threads);
                #else
                        init.initialize(threads);
                #endif
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
