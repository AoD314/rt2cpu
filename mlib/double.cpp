
#include "mlib/double.hpp"

#include <limits>
#include <sstream>


namespace mlib
{
    double Double::Parce(std::string val)
    {
        std::istringstream i(val);
        double x;

        if (!(i >> x)) return 0;

        return x;
    }

    int Double::SizeOfByte()
    {
        return sizeof(double);
    }

    double Double::MaxValue()
    {
        return std::numeric_limits<double>::max ();
    }

    double Double::MinValue()
    {
        return std::numeric_limits<double>::min ();
    }

    std::string Double::ToString(double val)
    {
        std::ostringstream s;
        s << val;
        return s.str();
    }
}

