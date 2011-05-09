
#include <iostream>

#include <mlib/fixed_vector.hpp>
#include <mlib/timer.hpp>
#include <mlib/console_parameters.hpp>
#include <mlib/randomize.hpp>

#include <valarray>

using namespace std;
using namespace mlib;

inline vec4 test_et1(const vec4 & a, const vec4 & b)
{
        return dot(b - 0.75f * a, b * dot(a,b-a)) * b + 0.0025f * a * b * dot(a, b);
}

typedef valarray<float> vecf;

inline float dot(const vecf & a, const vecf & b)
{
        return a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
}

inline vecf test_woet1(const vecf & a, const vecf & b)
{
        vecf t1 = b - vecf(0.75f) * a;
        vecf t2 = b - a;
        vecf t3 = b * vecf(dot(a, t2));
        return vecf(dot(t1, t3)) * b + vecf(0.0025f) * a * b * vecf(dot(a, b));
}

TimerModeCount get_mode(int i)
{
        if (i == 0) return mode_min;
        if (i == 1) return mode_avg;
        if (i == 2) return mode_max;
        if (i == 3) return mode_sum;
}

int main(int argc, char ** argv)
{
        ConsoleParameters params(argc, argv);
        size_t count = params.get(" -c | --count ", 1000);
        int mode     = params.get(" -m | --mode  ", 0);

        Timer timer(1, get_mode(mode));

        Rand::Randomize();
        vec4 h(Rand::NextFloat()), j(Rand::NextFloat());

        for (size_t i = 0; i < count; i++)
        {
                timer.Start();
                h = test_et1(h, j);
                j = test_et1(j, h);
                timer.Stop();
        }

        size_t tt1 = timer.GetTotalTimeInTick();

        timer.Reset();
        vecf hf(Rand::NextFloat(), 4), jf(Rand::NextFloat(), 4);

        for (size_t i = 0; i < count; i++)
        {
                timer.Start();
                hf = test_woet1(hf, jf);
                jf = test_woet1(jf, hf);
                timer.Stop();
        }

        size_t tt2 = timer.GetTotalTimeInTick();

        cout << "time: " << tt1 << "/" << tt2 << endl;
        cout << h << j << endl;
        cout << hf[0] << jf[0] << endl;

        return 0;
}
