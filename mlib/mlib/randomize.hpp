
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
            static int Next();
            static int Next(unsigned int from, unsigned int to);
    };
}

#endif
