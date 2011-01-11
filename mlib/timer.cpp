
#include "mlib/timer.hpp"

namespace mlib
{
	void Timer::CalcSec()
	{
		time_total    += time_last;
		seconds_last  = static_cast<double>(time_last) / static_cast<double>(GetFrequency());
		seconds_total += seconds_last;
	}

	void Timer::Reset()
	{
		time_total = 0;
		seconds_total = 0.0;
	}

	unsigned long long Timer::GetTimeInTick()
	{
		return time_last;
	}

	unsigned long long Timer::GetTotalTimeInTick()
	{
		return time_total;
	}

	Timer::Timer()
	{
		Reset();
		mode = inAll;
		fr = Processor::GetFrequency();
	}

	unsigned long long Timer::GetFrequency()
	{
		return fr;
	}

	double Timer::OperationPerSecond()
	{
		return 1.0 / seconds_last;
	}


	double Timer::GetTimeInSeconds ()
	{
		return seconds_last;
	}

	double Timer::GetTimeInMinutes ()
	{
		return seconds_last / 60.0f;
	}

	double Timer::GetTimeInHours ()
	{
		return seconds_last / (60.0f * 60.0f);
	}

	double Timer::GetTimeInDays ()
	{
		return seconds_last / (60.0f * 60.0f * 24.0f);
	}

	double Timer::GetTotalTimeInSeconds ()
	{
		return seconds_total;
	}

	double Timer::GetTotalTimeInMinutes ()
	{
		return seconds_total / 60.0f;
	}

	double Timer::GetTotalTimeInHours ()
	{
		return seconds_total / (60.0f * 60.0f);
	}

	double Timer::GetTotalTimeInDays ()
	{
		return seconds_total / (60.0f * 60.0f * 24.0f);
	}

	void Timer::SetMode(TimerModePrint m)
	{
		mode = m;
	}

	std::ostream & operator << (std::ostream& out, const Timer & t)
	{
		if (t.mode == inSec)
		{
			out << t.seconds_total << " sec";
		} else if (t.mode == inMin)
		{
			out << t.seconds_total / 60.0f  << " min";
		} else if (t.mode == inHour)
		{
			out << t.seconds_total / (60.0f * 60.0f) << " h";
		} else if (t.mode == inDays)
		{
			out << t.seconds_total / (60.0f * 60.0f * 24.0f) << " d";
		} else if (t.mode == inAll)
		{
			double sec = t.seconds_total;
			unsigned long long  timed = ( unsigned long long  ) sec / 86400;
			sec -= timed * 86400;

			unsigned long long  timeh = ( unsigned long long ) sec / 3600;
			sec -= timeh * 3600;

			unsigned long long timem = ( unsigned long long  ) sec / 60;
			sec -= timem * 60;

			out << timed << " days " << timeh << "h  " << timem << "m  " << std::fixed << std::setprecision(10) << sec << "s";
		}

		return out;
	}
}

