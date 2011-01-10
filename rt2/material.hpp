
#ifndef __material_hpp__
#define __material_hpp__

#include "texture.hpp"

#include "smath.hpp"

using namespace texture;
using namespace mlib;

namespace material
{
        class Material
        {
                protected:
                        size_t count_texture;

                        float * tkoeff;

                        float shininess;

                        Texture ** obj_texture;

                        vec4 Ka;
                        vec4 Ks;
                        vec4 Kd;

                        vec4 Kr;
                        size_t p;

                public:

                        Material ();

                        void AddTexture(Texture* t);

                        virtual vec4 GetColor(vec4& v) = 0;

                        void SetColor(vec4& a, vec4& d, vec4& s, vec4& r, float sh = 8);

                        vec4 GetColorAmbient();

                        vec4 GetColorDeffuse();

                        vec4 GetColorSpecular();

                        vec4 GetColorReflection();

                        float GetShininess();
        };

        class MaterialSimple : public Material
        {
                public:
                        vec4 GetColor(vec4& v);
        };

}

#endif

