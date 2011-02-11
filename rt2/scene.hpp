
#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <string>
#include <vector>

#include "triangle.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "ray.hpp"
#include "bvh.hpp"

namespace rt2
{
	class Scene
	{
		private:
                        BVH * bvh;
			Camera cam;

		public:
			Scene();
			Scene(Camera c);

			void load_from_file(const std::string & namefile);
			Camera get_cam();

                        Triangle * crossing (Ray & ray, float & t);

                        ~Scene();
	};

}

#endif
