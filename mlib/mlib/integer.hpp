

#ifndef __INTEGER_HPP__
#define __INTEGER_HPP__

#include <string>
#include <sstream>
#include <limits>

using namespace std;

namespace mlib
{
    class Int
    {
        public:
            static int Parce(string val);
            static string ToString (int val);
            static string ToString (int val, std::size_t width);
            static int MaxValue();
            static int MinValue();
            static int SizeOfByte();
    };
}

#endif


