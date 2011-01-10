
#include "mlib/float.hpp"

namespace mlib
{
    float Float::Parce(string val)
    {
        std::istringstream i(val);
        float x;

        if (!(i >> x)) return 0;

        return x;
    }

    float Float::MaxValue()
    {
        return numeric_limits<float>::max ();
    }

    float Float::MinValue()
    {
        return numeric_limits<float>::min ();
    }

    int Float::SizeOfByte()
    {
        return sizeof(float);
    }

    string Float::ToString(float val)
    {
        std::ostringstream s;
        s << val;
        return s.str();
    }

}
