
#include "primitives.hpp"

namespace primitives
{
	Primitives::Primitives()
	{
		position.zero ();
		orientation.zero();
	}

	Primitives::Primitives(vec4& _p, vec4& _d)
	{
		position = _p;
		orientation = Normalize(_d);
	}

	Material* Primitives::Materials()
	{
		return mtr;
	}

	void Primitives::SetMaterial(Material* m)
	{
		mtr = m;
	}


}

