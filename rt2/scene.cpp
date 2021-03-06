
#include <iostream>

#include "scene.hpp"

#include <mlib/objfile.hpp>
#include <mlib/float.hpp>
using namespace mlib;
using namespace std;

namespace rt2
{
        Scene::Scene(Camera * c, Light * l, int cl)

	{
		cam = c;
                bvh = NULL;
                lights = l;
                count_lights = cl;
                max_count_objects_in_bvh = 16;
	}

        void Scene::SetMaxCountObjectsInBVH(int max_count)
        {
                max_count_objects_in_bvh = max_count;
        }

        int Scene::get_lights()
        {
                return count_lights;
        }

        Light & Scene::get_light(int i)
        {
                return lights[i];
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
                v.push_back( new Triangle
                (
                        vec4( 2.0f, -1.25f,  2.0f, 0.0f),
                        vec4(-2.0f, -1.25f,  2.0f, 0.0f),
                        vec4(-2.0f, -1.25f, -2.0f, 0.0f)
                ));

                v.push_back( new Triangle
                (
                        vec4( 2.0f, -1.25f,  2.0f, 0.0f),
                        vec4(-2.0f, -1.25f, -2.0f, 0.0f),
                        vec4( 2.0f, -1.25f, -2.0f, 0.0f)
                ));
                //*/


                /*/
                v.push_back(new Sphere(vec4(-7.0f, 0.0f, -4.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-7.0f, 0.0f,  0.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-7.0f, 0.0f,  4.0f, 0.0f), 2.5f));

                v.push_back(new Sphere(vec4(-8.0f, 4.0f, -4.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-7.0f, 4.0f,  0.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-8.0f, 4.0f,  4.0f, 0.0f), 2.5f));

                v.push_back(new Sphere(vec4(-8.0f, -4.0f, -4.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-7.0f, -4.0f,  0.0f, 0.0f), 2.5f));
                v.push_back(new Sphere(vec4(-8.0f, -4.0f,  4.0f, 0.0f), 2.5f));
                //*/

                //*/
                //v.push_back(new Plane(vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f)));
                //*/

                v.push_back(new Sphere(vec4(0.45f, 1.30f, -0.15f, 0.0f), 0.30f));

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

        Camera * Scene::get_cam()
	{
                return cam;
	}

        Primitive * Scene::crossing(const Ray & ray, float & t)
	{
                return bvh->crossing(ray, t);
	}

        Scene::~Scene()
        {
        }

}
