
#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include <mlib/fixed_vector.hpp>

class Light
{
        private:
                mlib::vec4 p;
                float intens;
        public:
                Light();
                void set(mlib::vec4 pos, float intens);
                mlib::vec4 pos();
                mlib::vec4 color();
};

#endif
