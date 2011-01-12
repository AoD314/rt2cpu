
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
	vec4 a (1.0f, 0.0f, 3.0f, 0.0f);
	vec4 b (4.0f, 0.0f, 2.0f, 1.0f);
	vec4 c = a + b;
	return  c[0] == 5.0f && c[1] == 0.0f && c[2] == 5.0f && c[3] == 1.0f;
}

bool test_mlib_fixed_vector_sub()
{
	vec4 a (3.0f, 1.0f, 3.0f, 1.0f);
	vec4 b (a);
	vec4 c = a - b;
	return  c[0] == 0.0f && c[1] == 0.0f && c[2] == 0.0f && c[3] == 0.0f;
}

bool test_mlib_fixed_vector_double_add()
{
	vec4 a (1.0f, 1.0f, 1.0f, 0.0f);
	vec4 b (2.0f, 2.0f, 2.0f, 0.0f);
	vec4 c (3.0f, 3.0f, 3.0f, 0.0f);
	vec4 d = a + b + c;
	return d[0] == 6.0f && d[1] == 6.0f && d[2] == 6.0f && d[3] == 0.0f;
}

bool test_mlib_fixed_vector_complex_add()
{
	vec4 a (1.0f, 1.0f, 1.0f, 1.0f);
	vec4 b (2.0f, 2.0f, 2.0f, 2.0f);
	vec4 c (2.0f, 1.0f, 2.0f, 1.0f);
	vec4 d (1.0f, 3.0f, -3.0f, -5.0f);
	vec4 e;
	e = (a + b) + (c + d);
	return e[0] == 6.0f && e[1] == 7.0f && e[2] == 2.0f && e[3] == -1.0f;
}

bool test_mlib_fixed_vector_add_and_sub()
{
	vec4 a (1.0f, 1.0f, 1.0f, 1.0f);
	vec4 b (2.0f, 2.0f, 2.0f, 2.0f);
	vec4 c (2.0f, 1.0f, 2.0f, 1.0f);
	vec4 d (1.0f, 3.0f, -3.0f, -5.0f);
	vec4 e = b - a - c + d;
	return e[0] == 0.0f && e[1] == 3.0f && e[2] == -4.0f && e[3] == -5.0f;
}

bool test_mlib_fixed_vector_mul()
{
	vec4 a (1.0f, 2.0f, 3.0f,  3.0f);
	vec4 b (2.0f, 2.0f, 1.0f, -3.0f);
	vec4 c = a * b;
	return c[0] == 2.0f && c[1] == 4.0f && c[2] == 3.0f && c[3] == -9.0f;
}

bool test_mlib_fixed_vector_complex_mul()
{
	vec4 a (1.0f, 2.0f,  3.0f,  3.0f);
	vec4 b (2.0f, 2.0f,  1.0f, -3.0f);
	vec4 c (1.0f, 3.0f, -2.0f, -2.0f);
	vec4 d = a * b * c;
	return d[0] == 2.0f && d[1] == 12.0f && d[2] == -6.0f && d[3] == 18.0f;
}

bool test_mlib_fixed_vector_mul_num()
{
	vec4 a (1.0f, 2.0f,  3.0f, -1.0f);
	vec4 b = a * 3.0f;
	return b[0] == 3.0f && b[1] == 6.0f && b[2] == 9.0f && b[3] == -3.0f;
}

bool test_mlib_fixed_vector_complex_mul_num()
{
	vec4 a (2.0f, 2.0f,  5.0f, -2.0f);
	vec4 b (1.0f, 0.0f,  2.0f, -1.0f);
	vec4 c = 2.0f * a - 3.0f * b;
	return c[0] == 1.0f && c[1] == 4.0f && c[2] == 4.0f && c[3] == -1.0f;
}

bool test_mlib_fixed_vector_complex_operation()
{
	vec4 a ( 2.0f,  2.0f, 5.0f, -2.0f);
	vec4 b ( 1.0f,  1.0f, 0.0f, -1.0f);
	vec4 c ( 3.0f,  2.0f, 0.0f, -7.0f);
	vec4 d ( 8.0f,  3.0f, 4.0f,  0.0f);
	vec4 e (-1.0f, -5.0f, 3.0f, -1.0f);
	vec4 f = 2.0f * a - 3.0f * b * c + 2.0f * ( d - e );
	return f[0] == 13.0f && f[1] == 14.0f && f[2] == 12.0f && f[3] == -23.0f;
}

bool test_mlib_fixed_vector_dot()
{
	vec4 a ( -1.0f, 3.0f, 5.0f, -2.0f);
	vec4 b (  3.0f, 7.0f, 0.0f,  1.0f);
	float d = dot(a,b);
	return d == 16.0f;
}

bool test_mlib_fixed_vector_complex_dot()
{
	vec4 a ( 2.0f,  2.0f, 5.0f, -3.0f);
	vec4 b ( 1.0f,  1.0f, 0.0f,  1.0f);
	vec4 c ( 2.0f, -1.0f, 2.0f,  2.0f);
	float d = dot(2.0f * a, b + c);
	return d == 14.0f;
}

bool test_mlib_fixed_vector_calc_reflect()
{
	vec4 n (  2.0f, 3.0f, 0.0f, -3.0f);
	vec4 i ( -4.0f, 7.0f, 3.0f,  1.0f);
	vec4 r;
	r = i - 2.0f * n * dot (n, i);
	return r[0] == -44.0f && r[1] == -53.0f && r[2] == 3.0f && r[3] == 61.0f;
}

bool test_mlib_fixed_vector_to_color_b()
{
	vec4 Ia ( 0.0f, 0.0f, 1.0f, 1.0f);
	size_t color = to_color(Ia);
	return color == 255;
}

bool test_mlib_fixed_vector_to_color_rgb()
{
	vec4 Ia ( 0.25f, 0.5f, 1.0f, 0.0f);
	size_t color = to_color(Ia);
	return color == 4161535;
}

bool test_mlib_fixed_vector_vec_normalize()
{
	vec4 a ( 0.0f, 3.0f, 4.0f, 0.0f);
	a.normalize();
	return a[0] == 0.0f && a[1] == 0.6f && a[2] == 0.8f && a[3] == 0.0f;
}

bool test_mlib_fixed_vector_normalize()
{
	vec4 a ( 0.0f, 3.0f, 4.0f, 0.0f);
	vec4 b;
	b = normalize(a);
	return b[0] == 0.0f && b[1] == 0.6f && b[2] == 0.8f && b[3] == 0.0f;
}

bool test_mlib_fixed_vector_calc_distance()
{
	vec4 a ( 0.0f,  3.0f, 4.0f, 0.0f);
	vec4 b ( 1.0f, -2.0f, 1.0f, 1.0f);
	float d = calc_distance( a , b );
	return d == 6.0f;
}

bool test_mlib_fixed_vector_cross()
{
	vec4 a ( 2.0f,  0.0f,  4.0f, 2.0f);
	vec4 b ( 1.0f, -2.0f, -1.0f, 1.0f);
	vec4 c = cross ( a, b );
	return c[0] == 8.0f && c[1] == 6.0f && c[2] == -4.0f && c[3] == 0.0f;
}

bool test_mlib_min_and_max()
{
	return min(3,4) == 3 && max(4,5) == 5;
}

bool test_mlib_min_and_max_vec()
{
	vec4 a ( 1.0f, 2.0f, 3.0f, 4.0f );
	vec4 b ( 4.0f, 3.0f, 2.0f, 1.0f );
	vec4 mn = min(a,b);
	vec4 mx = max(a,b);
	return  mn[0] == 1.0f && mn[1] == 2.0f && mn[2] == 2.0f && mn[3] == 1.0f &&
		mx[0] == 4.0f && mx[1] == 3.0f && mx[2] == 3.0f && mx[3] == 4.0f;
}


/*
bool test_mlib_fixed_vector_()
{
	return [0] == .0f && [1] == .0f && [2] == .0f && [3] == .0f;
}
*/

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

	TEST (test_mlib_fixed_vector_add,                      "mlib_fixed_vector_add")
	TEST (test_mlib_fixed_vector_double_add,               "mlib_fixed_vector_double_add")
	TEST (test_mlib_fixed_vector_complex_add,              "mlib_fixed_vector_complex_add")
	TEST (test_mlib_fixed_vector_sub,                      "mlib_fixed_vector_sub")
	TEST (test_mlib_fixed_vector_add_and_sub,              "mlib_fixed_vector_add_and_sub")
	TEST (test_mlib_fixed_vector_mul,                      "mlib_fixed_vector_mul")
	TEST (test_mlib_fixed_vector_complex_mul,              "mlib_fixed_vector_complex_mul")
	TEST (test_mlib_fixed_vector_mul_num,                  "mlib_fixed_vector_mul_num")
	TEST (test_mlib_fixed_vector_complex_mul_num,          "mlib_fixed_vector_complex_mul_num")
	TEST (test_mlib_fixed_vector_complex_operation,        "mlib_fixed_vector_complex_operation")
	TEST (test_mlib_fixed_vector_dot,                      "mlib_fixed_vector_dot")
	TEST (test_mlib_fixed_vector_complex_dot,              "mlib_fixed_vector_complex_dot")
	TEST (test_mlib_fixed_vector_calc_reflect,             "mlib_fixed_vector_calc_reflect")
	TEST (test_mlib_fixed_vector_to_color_b,               "mlib_fixed_vector_to_color_b")
	TEST (test_mlib_fixed_vector_to_color_rgb,             "mlib_fixed_vector_to_color_rgb")
	TEST (test_mlib_fixed_vector_vec_normalize,            "mlib_fixed_vector_vec_normalize")
	TEST (test_mlib_fixed_vector_normalize,                "mlib_fixed_vector_normalize")
	TEST (test_mlib_fixed_vector_calc_distance,            "mlib_fixed_vector_calc_distance")
	TEST (test_mlib_fixed_vector_cross,                    "mlib_fixed_vector_cross")

	TEST (test_mlib_min_and_max,                  "mlib_min_and_max")
	TEST (test_mlib_min_and_max_vec,              "mlib_min_and_max_vec")

	timer.Stop();
	
	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTimeInSeconds() << " sec. \n\n";

	return 0;
}

