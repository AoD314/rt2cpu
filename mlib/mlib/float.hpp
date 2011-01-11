
#ifndef __DOUBLE_HPP__
#define __DOUBLE_HPP__

#include <string>

namespace mlib
{
	class Float
	{
		public:
			static float Parce(std::string val);
			static std::string ToString(float val);
			static float MaxValue();
			static float MinValue();
			static int SizeOfByte();
	};
}

#endif

