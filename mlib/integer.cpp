
#include "mlib/integer.hpp"


namespace mlib
{
    int Int::Parce(string val)
    {
        std::istringstream i(val);
        int x;

        if (!(i >> x)) return 0;

        return x;
    }

    int Int::MaxValue()
    {
        return numeric_limits<int>::max ();
    }

    int Int::MinValue()
    {
        return numeric_limits<int>::min ();
    }

    string Int::ToString(int val)
    {
        std::ostringstream s;
        s << val;
        return s.str();
    }

    int Int::SizeOfByte()
    {
        return sizeof(int);
    }

    string Int::ToString (int val, std::size_t width)
    {
            string ret = Int::ToString(val);
            for (std::size_t i = ret.length(); i< width; i++) ret = "0" + ret;
            if (val >= 0)
            {
                for (std::size_t i = ret.length(); i < width; i++) ret = "0" + ret;
            }
            else
            {
                ret.erase(ret.begin(), ret.begin() + 1);
                for (std::size_t i = ret.length(); i < width - 1; i++) ret = "0" + ret;
                ret = "-" + ret;
            }
            return ret;
    }
}


