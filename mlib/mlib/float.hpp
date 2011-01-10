

#ifndef __DOUBLE_HPP__
#define __DOUBLE_HPP__

#include <string>
#include <sstream>
#include <limits>

using namespace std;

namespace mlib
{
    class Float
    {
        public:
            static float Parce(string val);
            static string ToString(float val);
            static float MaxValue();
            static float MinValue();
            static int SizeOfByte();
    };
}

#endif
