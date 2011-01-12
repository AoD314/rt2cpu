
#include "tests.hpp"
#define TEST(method, label) print_result ( method(), label, total_tests, total_good_tests );

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

bool print_debug_info;
Timer timer;
size_t N;

bool performance_test_ray_cross_triangle_ok()
{
	size_t count_tr = 0;

	vec4 point;

	timer.Start();

	for (size_t i = 0; i < N; i++)
	{
		float rand = static_cast<float>(Rand::Next(1,100));
		vec4 v0  (  0.0f, -4.0f, -3.0f, rand);
		vec4 v1  (  0.0f,  4.0f,  0.0f, rand);
		vec4 v2  (  0.0f, -4.0f,  3.0f, rand);
		vec4 pos (  4.0f,  0.0f,  0.0f, rand);
		vec4 dir ( -1.0f,  0.0f,  0.0f, rand);

		vec4 e1 = v1 - v0;
		vec4 e2 = v2 - v0;
		vec4 t = pos - v0;
		vec4 q = cross ( t, e1 );
		vec4 p = cross ( dir, e2 );

		vec4 tmp (dot(q,e2), dot(p,t), dot(q, dir), 0.0f);

		vec4 tuv = tmp * 1.0f / dot (p, e1);

		if (tuv >= vec4::zero() && (tuv[1] + tuv[2] <= 1.0f))
		{
			count_tr++;
			point = pos + tuv[0] * dir;
		}
	}

	timer.Stop();
	
	unsigned long long t = timer.GetTimeInTick();

	std::cout << "cross : " << count_tr << " / " << N << "\n";

	std::cout << "time ray cross triangle(" << N << ") : " << t << " tick. = " << t / N << " tick per one operation\n";

	return t < 314 * N;
}

bool performance_test_vector_add()
{
	vec4 a (1.0f, 2.0f, 3.0f, 4.0f);
	vec4 b (2.0f, 3.0f, 4.0f, 5.0f);
	vec4 c;

	timer.Start();

	for (size_t i = 0; i < N; i++)
	{
		c = a + b;
	}

	timer.Stop();
	
	unsigned long long t = timer.GetTimeInTick();

	std::cout << "vec : " << c << "\n";

	std::cout << "time vector add(" << N << ") : " << t << " tick. = " << t / N << " tick per one operation\n";

	return t < 3 * N;
}

bool performance_test_vector_big_add()
{
	vec4 a (1.0f, 2.0f, 33.0f, 4.0f);
	vec4 b (2.0f, 3.0f, -4.0f, 5.0f);
	vec4 c (2.0f, 5.0f, -2.0f, 5.0f);
	vec4 d (2.0f, 6.0f, -3.0f, 5.0f);
	vec4 e (2.0f, 7.0f, -4.0f, 5.0f);
	vec4 f (2.0f, 8.0f, -8.0f, 5.0f);
	vec4 g (2.0f, 0.0f, -9.0f, 5.0f);
	vec4 h;

	timer.Start();

	for (size_t i = 0; i < N; i++)
	{
		h = a + b + c + d + e + f + g;
	}

	timer.Stop();
	
	unsigned long long t = timer.GetTimeInTick();

	std::cout << "vec : " << h << "\n";
	
	std::cout << "time vector add(" << N << ") : " << t << " tick. = " << t / N << " tick per one operation\n";

	return t < 7 * N;
}


int main(int argc, char ** argv)
{
	Rand::Randomize();

	size_t total_tests = 0;
	size_t total_good_tests = 0;

	ConsoleParameters params(argc, argv);
	print_debug_info = params.has(" -p | --print ");
	N = params.get(" -c | --count ", 1000);

	if (params.has(" -h | --help | --usage "))
	{
		std::cout << "-p, --print    -- print debug info\n";
		std::cout << "-c, --count    -- count operations in tests\n";
		return 0;
	}

	std::cout << "Tests:\n";

	TEST (performance_test_vector_add,                 "performance_test_vector_add")
	TEST (performance_test_vector_big_add,             "performance_test_vector_big_add")
	TEST (performance_test_ray_cross_triangle_ok,      "performance_test_ray_cross_triangle_ok")

	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTotalTimeInSeconds() << " sec. \n\n";

	return 0;
}

