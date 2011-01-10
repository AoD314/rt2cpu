
#include "material.hpp"

namespace material
{
        Material::Material ( )
        {
                count_texture = 0;
                shininess = 2;
        }

        void Material::SetColor ( vec4& a, vec4& d, vec4& s, vec4& r, float sh )
        {
                Ka = a;
                Kd = d;
                Ks = s;
                Kr = r;
                shininess = sh;
        }

        void Material::AddTexture ( Texture * t )
        {
                size_t i;
                float tt = 1.0f / (count_texture + 1);

                Texture** temp;
                temp = new Texture*[count_texture + 1];

                float* tempkoeff;
                tempkoeff = new float[count_texture + 1];

                #pragma vector nontemporal
                for ( i = 0; i < count_texture; i++ )
                {
                        temp[i] = obj_texture[i];
                        tempkoeff[i] = tt;
                }

                temp[count_texture] = t;
                tempkoeff[count_texture] = tt;

                if ( count_texture > 0 )
                {
                        delete[] obj_texture;
                        delete[] tkoeff;
                }

                count_texture++;
                obj_texture = temp;
                tkoeff = tempkoeff;
        }

        vec4 Material::GetColorAmbient ( )
        {
            return Ka;
        }

        vec4 Material::GetColorDeffuse ( )
        {
            return Kd;
        }

        vec4 Material::GetColorSpecular ( )
        {
            return Ks;
        }

        vec4 Material::GetColorReflection ( )
        {
            return Kr;
        }

        float Material::GetShininess ( )
        {
            return shininess;
        }

        vec4 MaterialSimple::GetColor ( vec4& v )
        {
            vec4 temp;

            temp = obj_texture[0]->GetColor ( v );

            return temp;
        }

}
