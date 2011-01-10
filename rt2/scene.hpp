#ifndef __scene_hpp__
#define __scene_hpp__

#include <limits>

#include "lights.hpp"

#include "primitives.hpp"

#include "bvh-aabb.hpp"

#include "camera.hpp"

#include "ray.hpp"

using namespace light;
using namespace camera;
using namespace primitives;
using namespace ray;

namespace scene
{
        class Scene
        {
                private:
                    size_t obj_count;
                    size_t obj_size;

                    size_t light_count;
                    size_t light_size;

                    Primitives** obj_primitiv;

                    Lights** obj_light;

                    BVH * bvh;

                    Camera cam;

                public:
                    Scene();

                    Scene(Camera& c);

                    ~Scene();

                    Primitives* Crossing (Ray& r, vec4& point, bool use_bvh = false);

                    size_t GetCountObj();

                    size_t GetCountLight();

                    void allocate_p(std::size_t new_size);
                    void allocate_l(std::size_t new_size);

                    Lights* GetLights(size_t i);

                    void AddLight(Lights* l);

                    void AddLights(Lights** l, std::size_t count);

                    void AddPrimitives (Primitives* p);

                    Camera& GetCamera();

                    Scene (const Scene&);

                    Scene& operator = (const Scene&);

                    void GenBVH(std::size_t depth = 4);
        };

}

#endif
