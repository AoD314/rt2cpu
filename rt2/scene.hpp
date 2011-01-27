
#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include <string>
#include <vector>

#include "triangle.hpp"

namespace rt2
{
	class Scene
	{
		private:
			std::vector<Triangle> triangle_list;

		public:
			void load_from_file(const std::string & namefile);
	};

}

#endif
