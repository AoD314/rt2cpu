
#include <iostream>

#include "scene.hpp"

#include <mlib/objfile.hpp>
using namespace mlib;
using namespace std;

namespace rt2
{
	void Scene::load_from_file(const std::string & namefile)
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
		cout << "\ntotal triangles is " << obj.GetCountTriangle();
		cout.flush();
	}

	Camera Scene::get_cam()
	{
		return Camera(mlib::vec4::zero(), mlib::vec4::zero(), mlib::vec4::zero(), 64, 64, 45.0f);
	}

	unsigned int Scene::count_objects()
	{
		return triangle_list.size();
	}

	bool Scene::crossing(Ray & r)
	{
		for (unsigned int i = 0; i < triangle_list.size(); i++)
			triangle_list[i].is_cross(r);
		return true;
	}

}
