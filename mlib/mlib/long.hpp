
#ifndef __LONG_HPP__
#define __LONG_HPP__

#include <string>

namespace mlib
{
	class Long
	{
		public:
			static long long Parce(std::string val);
			static std::string ToString (long long val);
			static std::string ToString (long long val, std::size_t width);
			static long long MaxValue();
			static long long MinValue();
			static int SizeOfByte();
	};
}

#endif

