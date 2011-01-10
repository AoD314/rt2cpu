

#include "mlib/randomize.hpp"

namespace mlib
{
    void Rand::Randomize()
    {
        srand ( ( unsigned ) time ( NULL ) );
    }

    int Rand::Next ()
    {
        return rand();
    }

    int Rand::Next(unsigned int from, unsigned int to)
    {
        return ((rand()) % (to-from) + from);
    }

}
