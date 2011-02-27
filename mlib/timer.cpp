
#include "mlib/timer.hpp"

#include <limits>

namespace mlib
{
	void Timer::CalcSec()
	{
		count_time++;
		seconds_last  = static_cast<double>(time_last) / static_cast<double>(fr);
		seconds_total += seconds_last;
		seconds_min = (seconds_min > seconds_last) ? seconds_last : seconds_min ;
		seconds_max = (seconds_max < seconds_last) ? seconds_last : seconds_max ;

		time_total += time_last;
		time_min = ( time_min > time_last )? time_last : time_min;
		time_max = ( time_max < time_last )? time_last : time_max;
	}

	void Timer::Reset()
	{
		seconds_total = 0.0;
		seconds_last  = 0.0;
		seconds_min   = std::numeric_limits<double>::max();
		seconds_max   = std::numeric_limits<double>::min(); 

		time_total = 0;
		time_last  = 0;
		time_min   = std::numeric_limits<unsigned long long>::max();
		time_max   = std::numeric_limits<unsigned long long>::min();
		count_time = 0;
	}

	unsigned long long Timer::GetTimeInTick() const
	{
		return time_last;
	}

	unsigned long long Timer::GetTotalTimeInTick() const
	{
		unsigned long long ret = 0;

		if      (mode_c == mode_sum)
		{
			ret = time_total;
		}
		else if (mode_c == mode_min)
		{
			ret = time_min;
		}
		else if (mode_c == mode_max)
		{
			ret = time_max;
		}
		else if (mode_c == mode_avg)
		{
			ret = time_total / count_time;
		}

		return ret;
	}

	Timer::Timer(unsigned long long frequency, TimerModeCount mode)
	{
		Reset();
		mode_c = mode;
		mode_p = inAll;
		fr = frequency;
	}

	Timer::Timer(TimerModeCount mode)
	{
		Reset();
		mode_c = mode;
		mode_p = inAll;
		fr = Processor::GetFrequency();
	}

	unsigned long long Timer::GetFrequency() const
	{
		return fr;
	}

	double Timer::OperationPerSecond() const
	{
		return 1.0 / seconds_last;
	}

        double Timer::GetTimeInMSeconds () const
        {
                return GetTimeInSeconds() * 1000;
        }

	double Timer::GetTimeInSeconds () const 
	{
		return seconds_last;
	}

	double Timer::GetTimeInMinutes () const
	{
		return seconds_last / 60.0f;
	}

	double Timer::GetTimeInHours () const 
	{
		return seconds_last / (60.0f * 60.0f);
	}

	double Timer::GetTimeInDays () const
	{
		return seconds_last / (60.0f * 60.0f * 24.0f);
	}

	double Timer::GetTotalTimeInSeconds () const 
	{
		double ret = 0;

		if      (mode_c == mode_sum)
		{
			ret = seconds_total;
		}
		else if (mode_c == mode_min)
		{
			ret = seconds_min;
		}
		else if (mode_c == mode_max)
		{
			ret = seconds_max;
		}
		else if (mode_c == mode_avg)
		{
			ret = seconds_total / static_cast<double>(count_time);
		}

		return ret;
	}

        double Timer::GetTotalTimeInMSeconds () const
        {
                return GetTotalTimeInSeconds() * 1000;
        }


	double Timer::GetTotalTimeInMinutes () const
	{
		return GetTotalTimeInSeconds() / 60.0f;
	}

	double Timer::GetTotalTimeInHours () const
	{
		return GetTotalTimeInSeconds() / (60.0f * 60.0f);
	}

	double Timer::GetTotalTimeInDays () const 
	{
		return GetTotalTimeInSeconds() / (60.0f * 60.0f * 24.0f);
	}

	void Timer::SetMode(TimerModePrint m)
	{
		mode_p = m;
	}

	std::ostream & operator << (std::ostream& out, const Timer & t)
	{
		if (t.mode_p == inSec)
		{
			out << t.GetTotalTimeInSeconds() << " sec";
		} 
		else if (t.mode_p == inMin)
		{
			out << t.GetTotalTimeInMinutes() << " min";
		} 
		else if (t.mode_p == inHour)
		{
			out << t.GetTotalTimeInHours() << " h";
		} 
		else if (t.mode_p == inDays)
		{
			out << t.GetTotalTimeInDays()   << " d";
		} 
		else if (t.mode_p == inAll)
		{
			double sec = t.GetTotalTimeInSeconds();
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

