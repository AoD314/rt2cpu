
#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <mlib/fixed_vector.hpp>

class Light
{
        private:
                mlib::vec4 p;

        public:
                Light(mlib::vec4 pos, float intens);
                mlib::vec4 pos();
};

#endif
