
#include "scene.hpp"

namespace scene
{

        void Scene::GenBVH(std::size_t depth)
        {
                bvh = new BVH(obj_primitiv, obj_count, depth);
        }

        Scene::Scene ( Camera& c )
        {
                light_count = 0;
                light_size = 0;

                obj_count = 0;
                obj_size = 0;

                cam = c;
                obj_primitiv = 0;
                obj_light = 0;
        }

        void Scene::allocate_p(std::size_t new_size)
        {
                obj_size = new_size;

                size_t i;
                Primitives** temp;
                temp = new_memory<Primitives*>(new_size);

                for ( i = 0; i < obj_count - 1; i++ )
                        temp[i] = obj_primitiv[i];

                del_memory ( obj_primitiv );
                obj_primitiv = temp;
        }

        void Scene::allocate_l(std::size_t new_size)
        {
                light_size = new_size;

                size_t i;
                Lights** temp;
                temp = new_memory<Lights*>(new_size);

                for ( i = 0; i < light_count - 1; i++ )
                        temp[i] = obj_light[i];

                del_memory ( obj_light );
                obj_light = temp;
        }

        Scene::~Scene ( )
        {
                del_memory ( obj_primitiv );
                del_memory ( obj_light );
        }

        Scene::Scene ( )
        {
                light_count = 0;
                light_size = 0;
                obj_size = 0;
                obj_count = 0;
                obj_primitiv = 0;
                obj_light = 0;
        }

        Scene::Scene ( const Scene& s )
        {
                light_count = s.light_count;
                obj_count   = s.obj_count;
                light_size  = light_count;
                obj_size    = obj_count;

                obj_primitiv = new_memory<Primitives*>(obj_count);
                obj_light    = new_memory<Lights*>(light_count);
                cam = s.cam;
                size_t i;
                for ( i = 0; i < obj_count; i++ )   obj_primitiv[i] = s.obj_primitiv[i];
                for ( i = 0; i < light_count; i++ ) obj_light[i] = s.obj_light[i];
        }

        size_t Scene::GetCountObj ( )
        {
                return obj_count;
        }

        size_t Scene::GetCountLight ( )
        {
                return light_count;
        }

        Lights* Scene::GetLights ( size_t i )
        {
                return obj_light[i];
        }

        Scene& Scene::operator = ( const Scene& s)
        {
            if ( this != &s )
            {
                del_memory ( obj_primitiv );
                del_memory ( obj_light );

                light_count = s.light_count;
                obj_count   = s.obj_count;
                light_size = light_count;
                obj_size = obj_count;
                bvh = s.bvh;

                obj_primitiv = new_memory<Primitives*>(obj_count);
                obj_light = new_memory<Lights*>(light_count);
                cam = s.cam;
                size_t i;
                for ( i = 0; i < obj_count; i++ ) obj_primitiv[i] = s.obj_primitiv[i];
                for ( i = 0; i < light_count; i++ ) obj_light[i] = s.obj_light[i];
            }
            return *this;
        }

        Primitives* Scene::Crossing ( Ray& r, vec4& point, bool use_bvh )
        {
                Primitives* f = 0;

                if (use_bvh)
                {
                        f = bvh->crossing (r, point);
                }
                else
                {
                        vec4 ttt;
                        float dist = std::numeric_limits<float>::max ( );
                        float temp;
                        size_t i;

                        for ( i = 0; i < obj_count; i++ )
                        {

                                temp = obj_primitiv[i]->Crossing ( r, point );

                                if ( temp > 0 )
                                {
                                        if ( temp < dist )
                                        {
                                                f = obj_primitiv[i];
                                                dist = temp;
                                                ttt = point;
                                        }
                                }
                        }
                        point = ttt;
                }

                return f;
        }

        void Scene::AddLight ( Lights* l )
        {
                light_count++;

                if (light_count >= light_size)
                {
                        allocate_l (obj_size + 10);
                }

                obj_light[light_count-1] = l;

        }

        void Scene::AddLights ( Lights** l, std::size_t count )
        {

                if (light_count + count >= light_size)
                {
                        allocate_l (obj_size + count + 10);
                }

                for (std::size_t i = light_count; i < light_count + count; i++)
                        obj_light[i] = l[i - light_count];

        }

        void Scene::AddPrimitives ( Primitives* p )
        {
                obj_count++;

                if (obj_count >= obj_size)
                {
                        allocate_p (obj_size + 10);
                }

                obj_primitiv[obj_count-1] = p;
        }

        Camera& Scene::GetCamera ( )
        {
                return cam;
        }

}
