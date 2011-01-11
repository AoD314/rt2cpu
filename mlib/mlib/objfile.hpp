
#ifndef __OBJFILE_HPP__
#define __OBJFILE_HPP__

#include <string>
#include <vector>
#include <fstream>
#include <valarray>

#include "fixed_vector.hpp"

namespace mlib
{
	class Objfile
	{
		private:
			std::vector<std::valarray<float> >  v;  // array vertex
			std::vector<std::valarray<float> >  vn; // array normals
			std::vector<std::valarray<int> >    f;  // array face{набор вершин из которых можно собрать треугольники}
			std::vector<int>                    fn; // array face normal

		public:
			Objfile ();

			bool read (std::string filename);

			vec4 GetPointInTriangle   (size_t num_triangle, size_t num_vertex);
			vec4 GetNormalForTriangle (size_t num_triangle);
			size_t GetCountTriangle();
	};
}

#endif

/*

Example

# Blender3D v249 OBJ File:
# www.blender3d.org
mtllib my_cube.mtl
o Cube
v 1.000000 1.000000 -1.000000
v 1.000000 -1.000000 -1.000000
v -1.000000 -1.000000 -1.000000
v -1.000000 1.000000 -1.000000
v 1.000000 0.999999 1.000000
v 0.999999 -1.000001 1.000000
v -1.000000 -1.000000 1.000000
v -1.000000 1.000000 1.000000
vn 0.000000 1.000000 0.000000
vn -1.000000 0.000000 -0.000000
vn -0.000000 -1.000000 -0.000000
vn 1.000000 0.000000 -0.000000
vn 1.000000 -0.000001 0.000000
vn 0.000000 0.000000 1.000000
vn 0.000000 0.000000 -1.000000
usemtl Material
s off
f 5//1 1//1 8//1
f 1//1 4//1 8//1
f 3//2 7//2 8//2
f 3//2 8//2 4//2
f 2//3 6//3 3//3
f 6//3 7//3 3//3
f 1//4 5//4 2//4
f 5//5 6//5 2//5
f 5//6 8//6 7//6
f 5//6 7//6 6//6
f 1//7 2//7 3//7
f 1//7 3//7 4//7

*/
