
#include "mlib/processor.hpp"

namespace mlib
{
    unsigned long long Processor::GetOptimalThreads()
    {
        unsigned long long count_thread = 1;

        try
        {
                #pragma omp parallel
                #pragma omp master
                        count_thread = omp_get_max_threads ();
        }
        catch (...) {}

        return count_thread;
    }

    unsigned long long Processor::GetFrequency()
    {
        unsigned long long frequency = static_cast<unsigned long long>(2400000000);
        #ifdef WIN32
                unsigned int dwTimerHi, dwTimerLo;
                __asm
                {
                        rdtsc
                        mov dwTimerLo, EAX
                        mov dwTimerHi, EDX
                }
                Sleep (500);
                __asm
                {
                        rdtsc
                        sub EAX, dwTimerLo
                        sub EAX, dwTimerHi
                        mov dwTimerLo, EAX
                        mov dwTimerHi, EDX
                }
                frequency = static_cast<unsigned long long>(dwTimerLo/500)*(1000);
        #else
                register volatile unsigned int a asm ("eax");
                register volatile unsigned int d asm ("edx");
                register volatile unsigned int c asm ("ecx");
                asm volatile ("rdtscp");
                register volatile unsigned int time_edx = d;
                register volatile unsigned int time_eax = a;
                register volatile unsigned int context = c;

                sleep(1);

                c = context;
                asm volatile("rdtscp");
                frequency = ((unsigned long long)(d) << 32 | (unsigned long long)(a)) - ((unsigned long long)(time_edx) << 32 | (unsigned long long)(time_eax));
        #endif

        return frequency;
    }

    bool Processor::is_set_N_bit_in_EDX(int bit)
    {
        int func = 1, _eax, _edx, _ecx;

        asm volatile ("cpuid" : "=eax" (_eax), "=edx" (_edx), "=ecx" (_ecx) : "eax" (func));

        return ((_edx & (1 << bit)) >> bit);

    }

    bool Processor::is_set_N_bit_in_ECX(int bit)
    {
        int func = 1, _eax, _edx, _ecx;

        asm volatile ("cpuid" : "=eax" (_eax), "=edx" (_edx), "=ecx" (_ecx) : "eax" (func));

        return ((_ecx & (1 << bit)) >> bit);
    }

    bool Processor::supportSSE()
    {
        return is_set_N_bit_in_EDX(25);
    }

    bool Processor::supportSSE2()
    {
        return is_set_N_bit_in_EDX(26);
    }

    bool Processor::supportSSE3()
    {
        return is_set_N_bit_in_ECX(0);
    }

    bool Processor::supportSSSE3()
    {
        return is_set_N_bit_in_ECX(9);
    }

    bool Processor::supportSSE4_1()
    {
        return is_set_N_bit_in_ECX(19) && is_set_N_bit_in_ECX(9) && is_set_N_bit_in_ECX(0);
    }

    bool Processor::supportSSE4_2()
    {
        return is_set_N_bit_in_ECX(20) && is_set_N_bit_in_ECX(19) && is_set_N_bit_in_ECX(9);
    }

    bool Processor::supportAVX()
    {
        return is_set_N_bit_in_ECX(28);
    }

    bool Processor::supportAES()
    {
        return is_set_N_bit_in_ECX(25);
    }

    bool Processor::supportPOPCNT()
    {
        return is_set_N_bit_in_ECX(23);
    }

    bool Processor::supportMMX()
    {
        return is_set_N_bit_in_EDX(23);
    }

    bool Processor::supportRDTSCP()
    {
        return is_set_N_bit_in_ECX(1);
    }

    bool Processor::supportHT()
    {
        return is_set_N_bit_in_EDX(28);
    }
}

