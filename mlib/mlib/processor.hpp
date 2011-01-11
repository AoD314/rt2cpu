
#ifndef __PROCESSOR_HPP__
#define	__PROCESSOR_HPP__

#include <omp.h>
#include <limits>

#ifdef WIN32
        #include <windows.h>
#else
        #include <unistd.h>
#endif

namespace mlib
{
	class Processor
	{
		public:
			static unsigned long long GetOptimalThreads();
			static unsigned long long GetFrequency();

			static bool supportSSE();
			static bool supportSSE2();
			static bool supportSSE3();
			static bool supportSSSE3();
			static bool supportSSE4_1();
			static bool supportSSE4_2();
			static bool supportAVX();
			static bool supportAES();
			static bool supportPOPCNT();
			static bool supportRDTSCP();
			static bool supportMMX();
			static bool supportHT();


			static bool is_set_N_bit_in_EAX(int bit);
			static bool is_set_N_bit_in_EBX(int bit);
			static bool is_set_N_bit_in_ECX(int bit);
			static bool is_set_N_bit_in_EDX(int bit);
	};
}

#endif

