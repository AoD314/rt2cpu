
#ifndef __pr_mesh_hpp__
#define __pr_mesh_hpp__

#include "primitives.hpp"
#include <limits>

#include <mlib/fixed_vector.hpp>
#include <mlib/list.hpp>
using namespace mlib;

namespace primitives
{
        class Mesh : public Primitives
        {
                private:
                        List<vec4> * points;
                        std::size_t count;

                public:
                        Mesh(size_t size = 1024 * 3);

                        void AddVec4(vec4 & v);

                        float Crossing (Ray& r, vec4& tp);

                        inline vec4 CalcNormal (vec4& tp);

                        ~Mesh();
        };

}

#endif

