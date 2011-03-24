
#include "light.hpp"

using namespace mlib;

Light::Light(){}

void Light::set(vec4 pos, float intens)
{
        p = pos;
        this->intens = intens;
}

vec4 Light::pos()
{
        return p;
}

vec4 Light::color()
{
        return vec4(intens);
}