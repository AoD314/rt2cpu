
#ifndef __RANDOMIZE_HPP__
#define	__RANDOMIZE_HPP__

#include <stdlib.h>
#include <time.h>

namespace mlib
{
	class Rand
	{
		public:
			static void Randomize();
			static size_t Next();
                        static float  NextFloat();
			static size_t Next(size_t from, size_t to);
	};
}

#endif

