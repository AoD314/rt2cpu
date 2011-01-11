
#ifndef __MMEMORY_HPP__
#define __MMEMORY_HPP__

#include <stdlib.h>
#include <malloc.h>
#include <cstddef>
#include <new>

namespace mlib
{
    template <typename T>
    T* new_memory(std::size_t count, int aligned = 16)
    {
        if (aligned == 0)
        {
            return new T[count];
        }
        else
        {
            T * ptr;
            #ifdef WIN32
                    ptr = static_cast<T*>(_aligned_malloc(sizeof (T) * count, aligned));
            #else
                    ptr = static_cast<T*>(memalign(aligned, sizeof (T) * count)); // posix
            #endif

            for (std::size_t i = 0; i < count; i++)
            {
                    T * p = ptr + i;
                    new(p) T;
            }

            return ptr;
        }
    }

    void del_memory(void* p);

}

#endif

