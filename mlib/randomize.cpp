
#include "mlib/randomize.hpp"
#include "mlib/integer.hpp"

namespace mlib
{
	void Rand::Randomize()
	{
		srand ( ( size_t ) time ( NULL ) );
	}

	size_t Rand::Next ()
	{
		return rand();
	}

	size_t Rand::Next(size_t from, size_t to)
	{
		return ((rand()) % (to-from) + from);
	}

        float Rand::NextFloat()
        {
                return static_cast<float>(rand()) / static_cast<float>(Int::MaxValue());
        }
}

