
#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <string>

namespace mlib
{
	class Int
	{
		public:
			static int Parce(std::string val);
			static std::string ToString (int val);
			static std::string ToString (int val, std::size_t width);
			static int MaxValue();
			static int MinValue();
			static int SizeOfByte();
	};
}

#endif

