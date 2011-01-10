#include <iostream>
#include <valarray>

#include "tests.hpp"

#include <timer.hpp>
#include <fixed_vector.hpp>
#include <double.hpp>
#include <long.hpp>


bool test_proc_sse()
{
    using namespace mlib;

    std::cout << "Processor:\n";

    std::cout << "MMX    : " << ( ( Processor::supportMMX()    == true ) ? "yes" : "no" ) << "\n";
    std::cout << "SSE    : " << ( ( Processor::supportSSE()    == true ) ? "yes" : "no" ) << "\n";
    std::cout << "SSE2   : " << ( ( Processor::supportSSE2()   == true ) ? "yes" : "no" ) << "\n";
    std::cout << "SSE3   : " << ( ( Processor::supportSSE3()   == true ) ? "yes" : "no" ) << "\n";
    std::cout << "SSSE3  : " << ( ( Processor::supportSSSE3()  == true ) ? "yes" : "no" ) << "\n";
    std::cout << "SSE4.1 : " << ( ( Processor::supportSSE4_1() == true ) ? "yes" : "no" ) << "\n";
    std::cout << "SSE4.2 : " << ( ( Processor::supportSSE4_2() == true ) ? "yes" : "no" ) << "\n";
    std::cout << "AVX    : " << ( ( Processor::supportAVX()    == true ) ? "yes" : "no" ) << "\n";
    std::cout << "AES    : " << ( ( Processor::supportAES()    == true ) ? "yes" : "no" ) << "\n";
    std::cout << "POPCNT : " << ( ( Processor::supportPOPCNT() == true ) ? "yes" : "no" ) << "\n";
    std::cout << "RDTSCP : " << ( ( Processor::supportRDTSCP() == true ) ? "yes" : "no" ) << "\n";
    std::cout << "HT     : " << ( ( Processor::supportHT()     == true ) ? "yes" : "no" ) << "\n";

    std::cout << "Cores  : " << Processor::GetOptimalThreads() << "\n";

    unsigned long long fr = Processor::GetFrequency();

    std::cout << "GetFrequency : " << fr << " = " << std::setprecision ( 4 ) << static_cast<float> ( fr ) / 1000000000 << " GHz\n";

    return true;
}

bool test_timer()
{
    using namespace mlib;
    Timer timer;

    double f = 1.0f;
    std::cout << "Start calc sin(f) ...\n";

    int count_iter;
    std::cout << "count iter: ";
    std::cin >> count_iter;

    timer.Start();

    for ( int i = 0; i < count_iter; i++ )
        f = sin ( f );

    timer.Stop();

    std::cout << "sin(f)  =  " << f <<  std::endl;

    std::cout << "time in fps : " << Double::ToString ( timer.OperationPerSecond() ) << " fps" <<  std::endl;
    std::cout << "time in tick: " << Long::ToString ( timer.GetTimeInTick() )      << " tick" <<  std::endl;
    std::cout << "time in sec : " << Double::ToString ( timer.GetTimeInSeconds() )   << " sec" <<  std::endl;
    std::cout << "time in all : " << timer <<  std::endl;

    std::cout << "time in tick per 1 iteration: " << Long::ToString ( timer.GetTimeInTick() / count_iter ) << " tick" << std::endl;

    size_t min_tick = Long::MaxValue();

    for ( size_t i = 0; i < 10000000; i++ )
    {
        timer.Reset();
        timer.Start();
        timer.Stop();
        if ( min_tick > timer.GetTimeInTick() )
            min_tick = timer.GetTimeInTick();
    }

    std::cout << "time min tick: " << Long::ToString ( min_tick ) << " tick" << std::endl;

    return true;
}

bool test_vectors()
{
    using namespace mlib;

    vec4 a ( 1.0f );
    vec4 b ( 0.0f );
    vec4 c ( 0.0f );

    Timer timer;
    timer.Start();

    c = a + a + a + a + a + b + b + b + b + b + c + c + c + c + c ;

    timer.Stop();

    std::cout << "vector a: " << a <<  std::endl;
    std::cout << "vector b: " << b <<  std::endl;
    std::cout << "vector c: " << c <<  std::endl;

    std::cout << "time in tick: " << Long::ToString ( timer.GetTimeInTick() ) << " tick" <<  std::endl << std::endl;

    return true;
}

bool test_comp_valarray()
{
    using namespace mlib;

    float r;
    std::cout << "read r: ";
    std::cin >> r;

    vec4 a ( 1.0f ), b ( r ), c ( 0.0f );

    Timer timer;
    timer.Start();

    c = b + b + b + b + b - a - a - a - a - a - a - a - a - a - a - a;

    timer.Stop();

    std::cout << "vector a: " << a <<  std::endl;
    std::cout << "vector b: " << b <<  std::endl;
    std::cout << "vector c: " << c <<  std::endl;
    std::cout << "vec4     time in tick: " << Long::ToString ( timer.GetTimeInTick() ) << " tick" <<  std::endl << std::endl;

    std::valarray<float> va ( 1.0f, 4 ), vb ( r, 4 ), vc ( 0.0f, 4 );

    timer.Reset();
    timer.Start();

    vc = vb + vb + vb + vb + vb - va - va - va - va - va - va - va - va - va - va - va;

    timer.Stop();

    std::cout << "vector a: " << va[0] << " " << va[1] << " " << va[2] << " " << va[3] << std::endl;
    std::cout << "vector b: " << vb[0] << " " << vb[1] << " " << vb[2] << " " << vb[3] <<  std::endl;
    std::cout << "vector c: " << vc[0] << " " << vc[1] << " " << vc[2] << " " << vc[3] <<  std::endl;
    std::cout << "valarray time in tick: " << Long::ToString ( timer.GetTimeInTick() ) << " tick" <<  std::endl << std::endl;

    return true;
}

int main()
{
    //print_result(test_proc_sse(),      "test processor"   );
    print_result ( test_timer(),         "test timer" );
    print_result ( test_vectors(),       "test vectors" );
    print_result ( test_comp_valarray(), "compare_valarray" );
    return 0;
}

