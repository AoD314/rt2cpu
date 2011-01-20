

#ifndef __RAY_HPP__
#define __RAY_HPP__

#include "mlib/fixed_vector.hpp"

namespace rt2
{
	class Ray
	{
		private:
			mlib::vec4 p, d;

		public:
			Ray(mlib::vec4 pos, mlib::vec4 dir);

			mlib::vec4 pos();
			mlib::vec4 dir();
	};

}

#endif

