
#include <iostream>

#include "scene.hpp"

#include <mlib/objfile.hpp>
using namespace mlib;
using namespace std;

namespace rt2
{
	Scene::Scene()
	{
		cam = Camera ( vec4( 5.0f, 0.0f, 0.0f, 0.0f), vec4(-1.0f, 0.0f, 0.0f, 0.0f), vec4( 0.0f, 1.0f, 0.0f, 0.0f), 256, 256, 60.0f);
	}

	Scene::Scene(Camera c)
	{
		cam = c;
	}

	Scene::Scene(const Scene & s)
	{
		cam = s.cam;
		triangle_list = s.triangle_list;
	}

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

                sphere = new Sphere(vec4(0.0f, 0.0f, 0.0f, 0.0f), 2.0f);
	}

	Camera Scene::get_cam()
	{
		return cam;
	}

	unsigned int Scene::count_objects()
	{
		return triangle_list.size();
	}

	Sphere * Scene::crossing(Ray & r)
	{
		if (sphere->is_cross(r))
			return sphere;
		return NULL;
	}

}
