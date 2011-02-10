
#include "tests.hpp"
#define TEST(method, label) print_result ( method(), label, total_tests, total_good_tests );

#include "triangle.hpp"
#include "sphere.hpp"
#include "ray.hpp"
#include "bbox.hpp"
#include "camera.hpp"

#include <mlib/console_parameters.hpp>
#include <mlib/timer.hpp>

using namespace mlib;
using namespace rt2;

bool print_debug_info;

bool test_rt2_camera_gen_ray_to_center()
{
	vec4 pos    ( 5.0f, 0.0f, 0.0f, 0.0f);
	vec4 dir    (-1.0f, 0.0f, 0.0f, 0.0f);
	vec4 dir_up ( 0.0f, 1.0f, 0.0f, 0.0f);

	Camera cam(pos, dir, dir_up, 640, 480, 60);
	Ray r = cam.get_ray(320, 240);
	return (r.dir()[0] == -1.0f) && (r.dir()[1] == 0.0f) && (r.dir()[2] == 0.0f) && (r.dir()[3] == 0.0f);
}

bool test_rt2_camera_gen_ray_to_up_right()
{
	vec4 pos    ( 5.0f, 0.0f, 0.0f, 0.0f);
	vec4 dir    (-1.0f, 0.0f, 0.0f, 0.0f);
	vec4 dir_up ( 0.0f, 1.0f, 0.0f, 0.0f);

	Camera cam(pos, dir, dir_up, 2048, 1024, 60);
	Ray r = cam.get_ray(0, 0);
	return (r.dir()[0] == -0.81321532f) && (r.dir()[1] == 0.26026174f) && (r.dir()[2] == 0.52052349f) && (r.dir()[3] == 0.0f);
}

bool test_rt2_camera_gen_ray_to_up_right_with_aa()
{
	vec4 pos    ( 5.0f, 0.0f, 0.0f, 0.0f);
	vec4 dir    (-1.0f, 0.0f, 0.0f, 0.0f);
	vec4 dir_up ( 0.0f, 1.0f, 0.0f, 0.0f);

	Camera cam(pos, dir, dir_up, 2048, 1024, 60);
	Ray r = cam.get_ray(0, 0, 0, 8);
	return (r.dir()[0] == -0.81321532f) && (r.dir()[1] == 0.26026174f) && (r.dir()[2] == 0.52052349f) && (r.dir()[3] == 0.0f);
}

bool test_rt2_ray_ok()
{
	vec4 pos (1.0f, 1.0f, 1.0f, 0.0f);
	vec4 dir (2.0f, 2.0f, 2.0f, 0.0f);
	Ray r(pos, dir);
	vec4 ret = r.pos();
	return (ret == pos) && (r.dir() == dir);
}

bool test_rt2_ray_nok()
{
	vec4 pos (1.0f, 1.0f, 1.0f, 0.0f);
	vec4 dir (2.0f, 2.0f, 2.0f, 0.0f);
	Ray r(pos, dir);
	pos = pos + dir;
	return (r.pos() != pos) && (r.dir() == dir);
}

bool test_rt2_bbox_cross()
{
	vec4 mn ( 4.0f, 0.0f, 0.0f, 0.0f);
	vec4 mx ( 0.0f, 4.0f, 4.0f, 0.0f);

	vec4 p ( 6.0f, 2.0f, 2.0f, 0.0f);
	vec4 d (-1.0f, 0.0f, 0.0f, 0.0f);

	Ray r(p,d);
	BBox box(mn, mx);

	return box.is_cross(r);
}

bool test_rt2_triangle_cross()
{
	vec4 a ( 3.0f, -1.0f, 0.0f, 0.0f);
	vec4 b ( 0.0f,  2.0f, 0.0f, 0.0f);
	vec4 c (-3.0f, -1.0f, 0.0f, 0.0f);

	vec4 p ( 0.0f, 0.0f,  3.0f, 0.0f);
	vec4 d ( 0.0f, 0.0f, -1.0f, 0.0f);

        Ray ray(p,d);
	Triangle t(a, b, c, a);

        return (t.crossing(ray) >= 0.0f);
}

bool test_rt2_triangle_cross_border()
{
        vec4 a ( 0.0f, 0.0f, 0.0f, 0.0f);
        vec4 b ( 0.0f, 1.0f, 0.0f, 0.0f);
        vec4 c ( 0.0f, 1.0f, 1.0f, 0.0f);
        vec4 n ( 1.0f, 0.0f, 0.0f, 0.0f);

        vec4 p ( 3.0f, 0.0f, 0.0f, 0.0f);
        vec4 d (-1.0f, 0.0f, 0.0f, 0.0f);

        Ray ray(p,d);
        Triangle t(a, b, c, n);

        return (t.crossing(ray) >= 0.0f);
}

bool test_rt2_triangle_cross_border_miss()
{
        vec4 a ( 0.0f, 0.0f, 0.0f, 0.0f);
        vec4 b ( 0.0f, 1.0f, 0.0f, 0.0f);
        vec4 c ( 0.0f, 1.0f, 1.0f, 0.0f);
        vec4 n ( 1.0f, 0.0f, 0.0f, 0.0f);

        vec4 p ( 3.0f, -0.5f, -0.5f, 0.0f);
        vec4 d (-1.0f,  0.0f,  0.0f, 0.0f);

        Ray ray(p,d);
        Triangle t(a, b, c, n);

        return (t.crossing(ray) < 0.0f);
}

bool test_rt2_triangle_cross_with_not_line_ray()
{
        vec4 a (  10.0f, -10.0f, -10.0f, 0.0f);
        vec4 b (   0.0f,  10.0f,   0.0f, 0.0f);
        vec4 c ( -10.0f, -10.0f,  10.0f, 0.0f);
        vec4 n ( 1.0f, 0.0f, 1.0f, 0.0f);

        vec4 p ( 2.0f,  2.0f,  2.0f, 0.0f);
        vec4 d (-1.0f, -1.0f, -1.0f, 0.0f);

        Ray ray(p, normalize(d));
        Triangle t(a, b, c, normalize(n));

        return (t.crossing(ray) >= 0.0f);
}

bool test_rt2_sphere_cross_in_center()
{
        vec4 p ( 3.0f,  0.0f, 0.0f, 0.0f);
        vec4 d ( -1.0f, 0.0f, 0.0f, 0.0f);

        Ray ray(p,d);

        Sphere s(vec4(), 1.0f);

        return s.crossing(ray) >= 0.0f;
}

bool test_rt2_sphere_cross_not_center()
{
        vec4 p ( 5.0f,  0.5f, 0.5f, 0.0f);
        vec4 d ( -1.0f, 0.0f, 0.0f, 0.0f);

        Ray ray(p,d);

        Sphere s(vec4(), 2.0f);

        return s.crossing(ray) >= 0.0f;
}

int main(int argc, char ** argv)
{
	size_t total_tests = 0;
	size_t total_good_tests = 0;

	ConsoleParameters params(argc, argv);
	print_debug_info = params.has(" -p | --print ");

	if (params.has(" -h | --help | --usage "))
	{
		std::cout << "-p, --print    -- print debug info\n";
		return 0;
	}

	std::cout << "Tests:\n";

	Timer timer;
	timer.Start();

	TEST (test_rt2_triangle_cross,                       "test_rt2_triangle_cross")
        TEST (test_rt2_triangle_cross_border,                "test_rt2_triangle_cross_border")
        TEST (test_rt2_triangle_cross_border_miss,           "test_rt2_triangle_cross_border_miss")
        TEST (test_rt2_triangle_cross_with_not_line_ray,     "test_rt2_triangle_cross_with_not_line_ray")

        TEST (test_rt2_sphere_cross_in_center,               "test_rt2_sphere_cross_in_center")
        TEST (test_rt2_sphere_cross_not_center,              "test_rt2_sphere_cross_not_center")
	TEST (test_rt2_bbox_cross,                           "test_rt2_bbox_cross")
	TEST (test_rt2_ray_ok,                               "test_rt2_ray_ok")
	TEST (test_rt2_ray_nok,                              "test_rt2_ray_nok")
	TEST (test_rt2_camera_gen_ray_to_center,             "test_rt2_camera_gen_ray_to_center")
	TEST (test_rt2_camera_gen_ray_to_up_right,           "test_rt2_camera_gen_ray_to_up_right")
	TEST (test_rt2_camera_gen_ray_to_up_right_with_aa,   "test_rt2_camera_gen_ray_to_up_right_with_aa")

	timer.Stop();

	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. "
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTimeInSeconds() << " sec. \n\n";

	return 0;
}

