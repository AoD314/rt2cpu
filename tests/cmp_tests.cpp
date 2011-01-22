
#include <valarray>

#include <mlib/console_parameters.hpp>
#include <mlib/timer.hpp>

#include <mlib/fixed_vector.hpp>
using namespace mlib;

bool print_debug_info;

unsigned long long FR;
TimerModeCount mode;

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

	Timer timer(FR, mode);

	for (size_t j = 0; j < N; j++)
	{
		timer.Start();
		r = i - std::valarray<float>(2.0f, 4) * n * std::valarray<float>((Dot(n, i),4));
		timer.Stop();
	}
	
	unsigned long long t = timer.GetTotalTimeInTick();

	std::cout << "reflection ray valarray : [ ";
	for (size_t i = 0; i < r.size(); i++) std::cout << r[i] << " ";
	std::cout << "]\n";

	std::cout << "time calc reflection ray (" << N << ") : " << t << " tick.\n";
}

void performance_test_reflection_ray_vec4()
{
	vec4 r;
	vec4 i ( -0.025f,  0.0005f,  0.0075f,  0.00025f);
	vec4 n ( 0.0075f,  0.0f,     0.00025f, 0.000005f);

	Timer timer(FR, mode);

	for (size_t j = 0; j < N; j++)
	{
		timer.Start();
		r = i - 2.0f * n * dot(n, i);
		timer.Stop();
	}
	
	unsigned long long t = timer.GetTotalTimeInTick();

	std::cout << "reflection ray vec4 : [ " << r << "]\n";

	std::cout << "time calc reflection ray (" << N << ") : " << t << " tick.\n";
}


int main(int argc, char ** argv)
{
	size_t total_tests = 0;
	size_t total_good_tests = 0;

	ConsoleParameters params(argc, argv);
	print_debug_info = params.has(" -p | --print ");
	N = params.get(" -c | --count ", 100);
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

	std::cout << "Tests:\n";

	Timer timer;
	FR = timer.GetFrequency();

	timer.Start();

	performance_test_reflection_ray_vec4();
	performance_test_reflection_ray_valarray();

	timer.Stop();

	std::cout.setf( std::ios::right );
	std::cout       << "\n" << std::setfill('0') << std::setw(3) << total_good_tests << " / " << std::setw(3) << total_tests << " passed. " 
			<< "       " << std::setw(3) << total_tests - total_good_tests <<  " errors.\n\n";
	std::cout << "Time: " << std::fixed << std::setprecision(8) << timer.GetTotalTimeInSeconds() << " sec. \n\n";

	return 0;
}

