
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
                max_count_objects_in_bvh = 32;
	}

	Scene::Scene(Camera c)
	{
		cam = c;
                bvh = NULL;
                max_count_objects_in_bvh = 32;
	}

        void Scene::SetMaxCountObjectsInBVH(int max_count)
        {
                max_count_objects_in_bvh = max_count;
        }

	void Scene::load_from_file(const std::string & namefile)
	{
		Objfile obj(namefile);
                vector<Primitive *> v;

                //*/
		for (size_t i = 0; i < obj.GetCountTriangle(); i++)
		{
                        v.push_back( new Triangle
			(
				obj.GetPointInTriangle(i, 0),
				obj.GetPointInTriangle(i, 1),
                                obj.GetPointInTriangle(i, 2)
			));
		}
                //*/
                cout << "total triangles is " << obj.GetCountTriangle() << "\n";
		cout.flush();

                /*/
                v.push_back(new Sphere(vec4(-7.0f, 0.0f, -5.5f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-7.0f, 0.0f,  0.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-7.0f, 0.0f,  5.5f, 0.0f), 2.5f));

                v.push_back(new Sphere(vec4(-8.0f, 4.5f, -4.5f, 0.0f), 1.5f));
                v.push_back(new Sphere(vec4(-7.0f, 4.5f,  0.0f, 0.0f), 1.5f));
                v.push_back(new Sphere(vec4(-8.0f, 4.5f,  4.5f, 0.0f), 1.5f));

                v.push_back(new Sphere(vec4(-8.0f, -4.5f, -4.5f, 0.0f), 1.5f));
                v.push_back(new Sphere(vec4(-7.0f, -4.5f,  0.0f, 0.0f), 1.5f));
                v.push_back(new Sphere(vec4(-8.0f, -4.5f,  4.5f, 0.0f), 1.5f));
                //*/

                /*/
                v.push_back(new Plane(vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f)));
                //*/

                /*/
                v.push_back(new Sphere(vec4(0.0f, 0.0f, 0.0f, 0.0f), 0.25f));
                int kkk = 2;
                for (int i=1; i < kkk; i++)
                        for (int j=1; j < kkk; j++)
                        {
                                v.push_back(new Sphere(vec4(0.0f,  i,  j, 0.0f), 0.25f));
                                v.push_back(new Sphere(vec4(0.0f, -i, -j, 0.0f), 0.25f));
                                v.push_back(new Sphere(vec4(0.0f,  i, -j, 0.0f), 0.25f));
                                v.push_back(new Sphere(vec4(0.0f, -i,  j, 0.0f), 0.25f));
                        }
                //*/

                cout << "total obj is " << v.size() << "\n";
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

        Primitive * Scene::crossing(const Ray & ray, float & t)
	{
                return bvh->crossing(ray, t);
	}

        Scene::~Scene()
        {
        }

}
