
#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <string>
#include <vector>

#include "triangle.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "ray.hpp"

namespace rt2
{
	class Scene
	{
		private:

			std::vector<Triangle> triangle_list;
                        std::vector<Sphere>   sphere_list;

			Camera cam;

		public:
			Scene();
			Scene(Camera c);
			Scene(const Scene & s);

			void load_from_file(const std::string & namefile);
			Camera get_cam();
			unsigned int count_objects();

                        Triangle * crossing_tr (Ray & r, float & t);
                        Sphere   * crossing_sph(Ray & r, float & t);
	};

}

#endif
