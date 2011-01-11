
#include <limits>
#include <sstream>

#include "mlib/long.hpp"

namespace mlib
{
	long long Long::Parce(std::string val)
	{
		std::istringstream i(val);
		long long x;

		if (!(i >> x)) return 0;
		return x;
	}

	long long Long::MaxValue()
	{
		return std::numeric_limits<long long>::max ();
	}

	long long Long::MinValue()
	{
		return std::numeric_limits<long long>::min ();
	}

	std::string Long::ToString(long long val)
	{
		std::ostringstream s;
		s << val;
		return s.str();
	}

	int Long::SizeOfByte()
	{
		return sizeof(long long);
	}

	std::string Long::ToString (long long val, std::size_t width)
	{
		std::string ret = Long::ToString(val);
		if (val >= 0)
		{
			for (std::size_t i = ret.length(); i < width; i++)
			ret = std::string("0") + ret;
		}
		else
		{
			ret.erase(ret.begin(), ret.begin() + 1);
			for (std::size_t i = ret.length(); i < width - 1; i++)
			ret = std::string("0") + ret;
			ret = "-" + ret;
		}
		return ret;
	}
}

