
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
                        int max_count_objects_in_bvh;

		public:
			Scene();
			Scene(Camera c);
                        Scene(const Scene & s);

			void load_from_file(const std::string & namefile);
			Camera get_cam();

                        void SetMaxCountObjectsInBVH(int max_count);

                        Triangle * crossing (Ray & ray, float & t);

                        ~Scene();
	};

}

#endif
