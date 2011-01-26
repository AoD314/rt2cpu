
#include "tests.hpp"
#define TEST(method, label) print_result ( method(), label, total_tests, total_good_tests );

#include <triangle.hpp>
#include <ray.hpp>

#include <mlib/console_parameters.hpp>
#include <mlib/timer.hpp>

#include <mlib/float.hpp>
#include <mlib/double.hpp>
#include <mlib/long.hpp>
#include <mlib/integer.hpp>
#include <mlib/randomize.hpp>
#include <mlib/fixed_vector.hpp>
#include <mlib/minmax.hpp>
using namespace mlib;
using namespace rt2;

bool print_debug_info;

unsigned long long FR;
TimerModeCount mode;

size_t N;

bool performance_test_ray_cross_triangle_ok()
{
	size_t count_tr = 0;

	vec4 point;

	Timer timer(FR, mode);

	for (size_t i = 0; i < N; i++)
	{
		float rand = static_cast<float>(Rand::Next(1,10));
		vec4 a ( 3.0f, -1.0f, 0.0f, rand);
		vec4 b ( 0.0f,  2.0f, 0.0f, rand);
		vec4 c (-3.0f, -1.0f, 0.0f, rand);

		vec4 p ( 0.0f, 0.0f,  3.0f, rand);
		vec4 d ( 0.0f, 0.0f, -1.0f, rand);

		rt2::Ray r(p, d);
		rt2::Triangle t(a, b, c, a);

		timer.Start();

		count_tr += ( t.is_cross(r) )? 1 : 0;

		timer.Stop();
	}

	unsigned long long t = timer.GetTotalTimeInTick();

	std::cout << "cross : " << count_tr << " / " << N << "\n";

	std::cout << "time ray cross triangle(" << N << ") : " << t << " tick.\n";

	return t <= 314 * N;
}

bool performance_test_vector_add()
{
	float rand = static_cast<float>(Rand::Next(1,100));
	vec4 a (0.025f, 0.025f, 0.0075f, rand / 1000.0f);
	vec4 c;

	Timer timer(FR, mode);

	for (size_t i = 0; i < N; i++)
	{
		timer.Start();

		c = a + c;

		timer.Stop();
	}


	unsigned long long t = timer.GetTotalTimeInTick();

	std::cout << "vec : " << c << "\n";

	std::cout << "time vector add(" << N << ") : " << t << " tick.\n";

	return t <= 5 * N;
}

bool performance_test_vector_big_add()
{
	float rand = static_cast<float>(Rand::Next(1,10)) / 1000000000.0f;
	vec4 a (0.0f, 0.00f, 0.00f,  rand);
	vec4 b (0.0f, 0.00f,  rand, 0.00f);
	vec4 c (rand, 0.00f, 0.00f, 0.00f);
	vec4 d (0.0f,  rand, 0.00f, 0.00f);
	vec4 e (rand, 0.00f, 0.00f, 0.00f);
	vec4 f (0.1f, -rand, 0.00f, 0.00f);
	vec4 g (0.0f, 0.00f, -rand, 0.00f);
	vec4 h;

	Timer timer(FR, mode);


	for (size_t i = 0; i < N; i++)
	{
		timer.Start();

		a = a + h;
		b = b + a;
		c = c + b;
		d = d + c;
		e = e + d;
		f = f + e;
		g = g + f;
		h = h + g;

		timer.Stop();
	}

	unsigned long long t = timer.GetTotalTimeInTick();

	std::cout << "vec : " << h << "\n";

	std::cout << "time vector add(" << N << ") : " << t << " tick.\n";

	return t <= 16 * N;
}

bool performance_test_timer()
{
	Timer timer(FR, mode);

	for (size_t i = 0; i < N; i++)
	{
		timer.Start();
		//std::cout << "X";
		timer.Stop();
	}

	unsigned long long t = timer.GetTotalTimeInTick();

	std::cout << "time std::cout(" << N << ") : " << t << " tick.\n";

	return t <= 101 * N;
}


int main(int argc, char ** argv)
{
	Rand::Randomize();

	size_t total_tests = 0;
	size_t total_good_tests = 0;

	ConsoleParameters params(argc, argv);
	print_debug_info = params.has(" -p | --print ");
	N = params.get(" -c | --count ", 1000);
	std::string mode_s = params.get<std::string>(" -m | --mode ", "min");

	if (mode_s.compare("min") == 0)
	{
		mode = mode_min;
	}
	else if (mode_s.compare("max") == 0)
	{
		mode = mode_max;
	}
	else if (mode_s.compare("sum") == 0)
	{
		mode = mode_sum;
	}
	else if (mode_s.compare("avg") == 0)
	{
		mode = mode_avg;
	}

	if (params.has(" -h | --help | --usage "))
	{
		std::cout << "-p, --print    -- print debug info\n";
		std::cout << "-c, --count    -- count operations in tests\n";
		std::cout << "-m, --mode {sum, max, min - by default, avg}\n";
		return 0;
	}

	Timer timer;
	FR = timer.GetFrequency();

	timer.Start();

	std::cout << "Tests:\n";

	TEST (performance_test_vector_add,                 "performance_test_vector_add")
	TEST (performance_test_vector_big_add,             "performance_test_vector_big_add")
	TEST (performance_test_ray_cross_triangle_ok,      "performance_test_ray_cross_triangle_ok")
	TEST (performance_test_timer,                      "performance_test_timer")

	timer.Stop();

	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. "
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTotalTimeInSeconds() << " sec. \n\n";

	return 0;
}

