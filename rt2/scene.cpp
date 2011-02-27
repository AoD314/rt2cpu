
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
                max_count_objects_in_bvh = 10000;
	}

	Scene::Scene(Camera c)
	{
		cam = c;
                bvh = NULL;
                max_count_objects_in_bvh = 10000;
	}

        void Scene::SetMaxCountObjectsInBVH(int max_count)
        {
                max_count_objects_in_bvh = max_count;
        }

	void Scene::load_from_file(const std::string & namefile)
	{

		Objfile obj(namefile);
                /*
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
                */
                cout << "total triangles is " << obj.GetCountTriangle() << "\n";
		cout.flush();

                vector<Primitive *> v;
                v.push_back(new Sphere(vec4(0.0f), 1.0f));
                v.push_back(new Sphere(vec4(1.0f), 1.0f));
                v.push_back(new Sphere(vec4(-1.0f), 1.0f));

                bvh = new BVH(v, max_count_objects_in_bvh);
	}

	Camera Scene::get_cam()
	{
		return cam;
	}

        Scene::Scene(const Scene & s)
        {
                bvh = s.bvh;
                cam = s.cam;
                max_count_objects_in_bvh = s.max_count_objects_in_bvh;
        }

        Primitive * Scene::crossing(Ray & ray, float & t)
	{
                return bvh->crossing(ray, t);
	}

        Scene::~Scene()
        {
        }

}
