
#include "ray.hpp"

namespace ray
{

	Ray::Ray ( ) { }

	Ray::Ray ( vec4& p, vec4& d )
	{
		pos = p;
		direction = Normalize(d);
	}

	vec4& Ray::Position ( )
	{
		return pos;
	}

	vec4& Ray::Direction ( )
	{
		return direction;
	}


}
