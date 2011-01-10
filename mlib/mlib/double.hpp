
#ifndef __DOUBLE_HPP__
#define __DOUBLE_HPP__

#include <string>

namespace mlib
{
class Double
{
public:
    static double Parce ( std::string val );
    static std::string ToString ( double val );
    static double MaxValue();
    static double MinValue();
    static int SizeOfByte();
};
}

#endif
