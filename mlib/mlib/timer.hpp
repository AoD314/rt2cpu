
#ifndef __TIMER_HPP__
#define	__TIMER_HPP__

#include <ostream>
#include <iomanip>

#include "processor.hpp"

namespace mlib
{
	enum TimerModePrint
	{
		inSec,
		inMin,
		inHour,
		inDays,
		inAll
	};

	enum TimerModeCount
	{
		mode_sum,
		mode_min,
		mode_max,
		mode_avg
	};

	class Timer
	{
		private:
			double seconds_total;
			double seconds_last;
			double seconds_min;
			double seconds_max;

			unsigned long long fr;
			unsigned long long time_total;
			unsigned long long time_last;
			unsigned long long time_min;
			unsigned long long time_max;
			unsigned long long count_time;

			unsigned int time_edx, time_edx1;
			unsigned int time_eax, time_eax1;;

			TimerModePrint mode_p;
			TimerModeCount mode_c;
			void CalcSec();

		public:
			Timer(TimerModeCount mode = mode_sum);
			Timer(unsigned long long frequency, TimerModeCount mode = mode_sum);

			inline void Start()
			{
				/*
				volatile register unsigned int a asm ("eax");
				volatile register unsigned int d asm ("edx");
				volatile register unsigned int c asm ("ecx");
				asm volatile ("rdtscp");
				time_edx = d;
				time_eax = a;
				context = c;
				*/
				asm volatile (  "cpuid\n\t"
						"rdtsc\n\t"
						"mov %%edx, %0\n\t"
						"mov %%eax, %1\n\t" : "=r"(time_edx), "=r"(time_eax) ::
						"%rax", "%rbx", "%rcx", "%rdx");
			}

			inline void Stop ()
			{
				asm volatile (  "rdtscp\n\t"
						"mov %%edx, %0\n\t"
						"mov %%eax, %1\n\t"
						"cpuid\n\t" : "=r"(time_edx1), "=r"(time_eax1) ::
						"%rax", "%rbx", "%rcx", "%rdx");
				
				/*volatile register unsigned int a asm ("eax");
				volatile register unsigned int d asm ("edx");
				volatile register unsigned int c asm ("ecx");
				c = context;
				asm volatile("rdtscp");
				*/

				time_last =     ((unsigned long long)(time_edx1) << 32 | (unsigned long long)(time_eax1)) - 
						((unsigned long long)(time_edx)  << 32 | (unsigned long long)(time_eax));
				CalcSec();
			}

			void Reset();

			void SetMode(TimerModePrint m);

			double OperationPerSecond() const;

			double GetTimeInSeconds() const;
			double GetTimeInMinutes() const;
			double GetTimeInHours() const;
			double GetTimeInDays() const;

			double GetTotalTimeInSeconds() const;
			double GetTotalTimeInMinutes() const;
			double GetTotalTimeInHours() const;
			double GetTotalTimeInDays() const;

			unsigned long long GetTimeInTick() const;
			unsigned long long GetTotalTimeInTick() const;
			unsigned long long GetFrequency() const;

			friend std::ostream & operator << (std::ostream& out, const Timer & t);
	};
}

#endif

