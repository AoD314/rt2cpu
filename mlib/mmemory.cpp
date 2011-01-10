
#include <stdlib.h>
#include <malloc.h>
#include <cstddef>

namespace mlib
{
    void del_memory(void* p)
    {
        #ifdef WIN32
            _aligned_free(p);
        #else
            free(p);
        #endif
    }
}
