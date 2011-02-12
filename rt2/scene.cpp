
#include <iostream>

#include "scene.hpp"

#include <mlib/objfile.hpp>
#include <mlib/float.hpp>
using namespace mlib;
using namespace std;

namespace rt2
{
	Scene::Scene()
	{
                cam = Camera ( vec4( 5.0f, 0.0f, 0.0f, 0.0f), vec4(-1.0f, 0.0f, 0.0f, 0.0f), vec4( 0.0f, 1.0f, 0.0f, 0.0f), 256, 256, 60.0f);
                bvh = NULL;
                max_count_objects_in_bvh = 16;
	}

	Scene::Scene(Camera c)
	{
		cam = c;
                bvh = NULL;
                max_count_objects_in_bvh = 16;
	}

        void Scene::SetMaxCountObjectsInBVH(int max_count)
        {
                max_count_objects_in_bvh = max_count;
        }

	void Scene::load_from_file(const std::string & namefile)
	{
		Objfile obj(namefile);
                vector<Triangle> triangle_list;

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

                bvh = new BVH(triangle_list, max_count_objects_in_bvh);
	}

	Camera Scene::get_cam()
	{
		return cam;
	}

        Triangle * Scene::crossing(Ray & ray, float & t)
	{
                return bvh->crossing(ray, t);
	}

        Scene::~Scene()
        {
                if (bvh != NULL)
                        delete bvh;
        }

}
