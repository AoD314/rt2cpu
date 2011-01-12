
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

bool test_mlib_float()
{
	float f = Float::Parce("1.25");
	std::string str = Float::ToString(f);
	return str == "1.25";
}
bool test_mlib_double()
{
	double d = Double::Parce("2.75");
	std::string str = Double::ToString(d);
	return str == "2.75";
}
bool test_mlib_int()
{
	int i = Int::Parce("6");
	std::string str = Int::ToString(i + 1);
	return str == "7";
}

bool test_mlib_long()
{
	long l = Long::Parce("-7");
	std::string str = Long::ToString(l);
	return str == "-7";
}

bool test_mlib_fixed_vector_add()
{
	vec4 a (1.0f, 2.0f, 3.0f, 4.0f);
	vec4 b (4.0f, 3.0f, 2.0f, 1.0f);
	vec4 c = a + b;
	
	vec4 d;

	d.set1(5.0f);

	return  Abs(dot(c - d, d - c)) <= 0.0000001f ;
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

	TEST (test_mlib_float,   "mlib_float")
	TEST (test_mlib_double,  "mlib_double")
	TEST (test_mlib_long,    "mlib_long")
	TEST (test_mlib_int,     "mlib_int")

	TEST (test_mlib_fixed_vector_add,     "mlib_fixed_vector_add")

	timer.Stop();
	
	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTimeInSeconds() << " sec. \n\n";

	return 0;
}

