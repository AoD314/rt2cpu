
#ifndef __texture_hpp__
#define __texture_hpp__

#include <mlib/fixed_vector.hpp>
using namespace mlib;

namespace texture
{

        class Texture
        {
        protected:
                vec4 color;

        public:
                Texture(vec4& c);

                virtual vec4& GetColor(vec4& coord) = 0;
        };

        class TextureColor : public Texture
        {
        public:
                TextureColor(vec4& c);

                vec4& GetColor(vec4& coord);
        };

}

#endif

