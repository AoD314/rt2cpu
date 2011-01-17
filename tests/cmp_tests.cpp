
#include <valarray>

#include <mlib/console_parameters.hpp>
#include <mlib/timer.hpp>

#include <mlib/fixed_vector.hpp>
using namespace mlib;

bool print_debug_info;
Timer timer;
size_t N;

float Dot (const std::valarray<float> & v1, const std::valarray<float> & v2)
{
	float dot = 0.0f;	

	for (size_t i = 0; i < std::min(v1.size(),v2.size()); i++)
		dot += v1[i] * v2[i];

	return dot;
}

void performance_test_reflection_ray_valarray()
{
	float ai[] = { -0.025f,  0.0005f,  0.0075f,  0.00025f };
	float an[] = { 0.0075f,  0.0f,     0.00025f, 0.000005f };
	std::valarray<float> r(0.0f, 4);
	std::valarray<float> i (ai, 4); 
	std::valarray<float> n (an, 4); 

	timer.Start();

	for (size_t j = 0; j < N; j++)
	{
		r = i - std::valarray<float>(2.0f, 4) * n * std::valarray<float>((Dot(n, i),4));
		i = r;
	}

	timer.Stop();
	
	unsigned long long t = timer.GetTimeInTick();

	std::cout << "reflection ray : [ ";
	for (size_t i = 0; i < r.size(); i++) std::cout << r[i] << " ";
	std::cout << "]\n";

	std::cout << "time calc reflection ray (" << N << ") : " << t << " tick. = " << t / N << " tick per one operation\n";
}

void performance_test_reflection_ray_vec4()
{
	vec4 r;
	vec4 i ( -0.025f,  0.0005f,  0.0075f,  0.00025f);
	vec4 n ( 0.0075f,  0.0f,     0.00025f, 0.000005f);

	timer.Start();

	for (size_t j = 0; j < N; j++)
	{
		r = i - 2.0f * n * dot(n, i);
		i = r;
	}

	timer.Stop();
	
	unsigned long long t = timer.GetTimeInTick();

	std::cout << "reflection ray : [ " << r << "]\n";

	std::cout << "time calc reflection ray (" << N << ") : " << t << " tick. = " << t / N << " tick per one operation\n";
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

	performance_test_reflection_ray_vec4();
	performance_test_reflection_ray_valarray();

	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTotalTimeInSeconds() << " sec. \n\n";

	return 0;
}

