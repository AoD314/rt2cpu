
#include "tests.hpp"
#define TEST(method, label) print_result ( method(), label, total_tests, total_good_tests );

#include "triangle.hpp"
#include "ray.hpp"
#include "bbox.hpp"

#include <mlib/console_parameters.hpp>
#include <mlib/timer.hpp>

using namespace mlib;
using namespace rt2;

bool print_debug_info;

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
	
	vec4 point;
	Ray r(p,d);
	Triangle t(a, b, c);

	return (t.crossing(r, point) >= 0.0f);
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

	TEST (test_rt2_triangle_cross,               "test_rt2_triangle_cross")
	TEST (test_rt2_bbox_cross,                   "test_rt2_bbox_cross")
	TEST (test_rt2_ray_ok,                       "test_rt2_ray_ok")
	TEST (test_rt2_ray_nok,                      "test_rt2_ray_nok")

	timer.Stop();
	
	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTimeInSeconds() << " sec. \n\n";

	return 0;
}

