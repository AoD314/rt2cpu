
#include "tests.hpp"
#define TEST(method, label) print_result ( method(), label, total_tests, total_good_tests );

#include <mlib/console_parameters.hpp>
#include <mlib/timer.hpp>

#include <mlib/float.hpp>
#include <mlib/double.hpp>
#include <mlib/long.hpp>
#include <mlib/integer.hpp>
#include <mlib/fixed_vector.hpp>
#include <mlib/minmax.hpp>
using namespace mlib;

bool print_debug_info;
Timer timer;
size_t N;

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

	std::cout << "c : " << c << "\n";

	std::cout << "time vector add(" << N << ") : " << t << " tick.\n";

	return t < 3 * N;
}

int main(int argc, char ** argv)
{
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

	TEST (performance_test_vector_add,   "performance_test_vector_add")

	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTotalTimeInSeconds() << " sec. \n\n";

	return 0;
}

