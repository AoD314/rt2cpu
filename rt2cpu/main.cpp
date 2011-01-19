
/// SDL ///

#include <SDL/SDL.h>

SDL_Surface *screen;

#define bpp 32

//////////

#include <iostream>

#include "settings.hpp"

#include <mlib/timer.hpp>
using namespace mlib;

int main ( int argc, char ** argv )
{
    try
    {
        Settings settings(argc, argv);
        if (settings.is_exit) return 0;
        settings.print_params();

        Timer timer;
        
        std::cout << "\nCPU Frequency: " << timer.GetFrequency() << std::endl;
        std::cout.flush();

	timer.Start();

        timer.Stop ();

        std::cout << "\n\nTotal time: " << timer << "\n";
    }
    catch (...) 
    {

    }
    return 0;
}

