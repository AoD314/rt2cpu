
#include "scene.hpp"

#include <mlib/objfile.hpp>
using namespace mlib;
using namespace std;

namespace rt2
{
	void Scene::load_from_file(std::string namefile)
	{
		Objfile obj(namefile);

		for (size_t i = 0; i < obj.GetCountTriangle(); i++)
		{
			triangle_list.push_back( Triangle
			(
				obj.GetPointInTriangle(i, 0),
				obj.GetPointInTriangle(i, 1),
				obj.GetPointInTriangle(i, 2),
				obj.GetNormalForTriangle(i)
			));
		}
	}

}
