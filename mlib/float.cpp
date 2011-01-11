
#include <sstream>
#include <limits>

#include "mlib/float.hpp"

namespace mlib
{
	float Float::Parce(std::string val)
	{
		std::istringstream i(val);
		float x;

		if (!(i >> x)) return 0;

		return x;
	}

	float Float::MaxValue()
	{
		return std::numeric_limits<float>::max ();
	}

	float Float::MinValue()
	{
		return std::numeric_limits<float>::min ();
	}

	int Float::SizeOfByte()
	{
		return sizeof(float);
	}

	std::string Float::ToString(float val)
	{
		std::ostringstream s;
		s << val;
		return s.str();
	}

}

