
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

	class Timer
	{
		private:
			double seconds_last;
			double seconds_total;
			unsigned long long fr;
			unsigned long long time_total;
			unsigned long long time_last;
			unsigned int time_edx;
			unsigned int time_eax;
			unsigned int context;

			TimerModePrint mode;
			void CalcSec();

		public:
			Timer();

			inline void Start()
			{
				register unsigned int a asm ("eax");
				register unsigned int d asm ("edxx");
				register unsigned int c asm ("ecx");
				asm volatile ("rdtscp");
				time_edx = d;
				time_eax = a;
				context = c;
			}

			inline void Stop ()
			{
				register unsigned int a asm ("eax");
				register unsigned int d asm ("edx");
				register unsigned int c asm ("ecx");
				c = context;
				asm volatile("rdtscp");
				time_last = ((unsigned long long)(d) << 32 | (unsigned long long)(a)) - ((unsigned long long)(time_edx) << 32 | (unsigned long long)(time_eax));
				CalcSec();
			}

			void Reset();

			void SetMode(TimerModePrint m);

			double OperationPerSecond();

			double GetTimeInSeconds();
			double GetTimeInMinutes();
			double GetTimeInHours();
			double GetTimeInDays();

			double GetTotalTimeInSeconds();
			double GetTotalTimeInMinutes();
			double GetTotalTimeInHours();
			double GetTotalTimeInDays();

			unsigned long long GetTimeInTick();
			unsigned long long GetTotalTimeInTick();
			unsigned long long GetFrequency();

			friend std::ostream & operator << (std::ostream& out, const Timer & t);
	};
}

#endif

