
/// SDL ///

#include <SDL/SDL.h>

SDL_Surface *screen;

#define bpp 32

//////////

#include <iostream>
#include <string>

#include "scene.hpp"
#include "engine.hpp"

#include "settings.hpp"

#include <mlib/timer.hpp>
#include <mlib/float.hpp>
#include <mlib/long.hpp>
#include <mlib/exception.hpp>
using namespace mlib;
using namespace rt2;
using namespace std;

unsigned int * InitSDL(const Settings & settings)
{
	unsigned int * buf;

	if ( (SDL_Init ( SDL_INIT_VIDEO )) < 0 )
	{
		printf ( "Don't init SDL: %s\n", SDL_GetError ( ) );
		return NULL;
	}

	screen = SDL_SetVideoMode ( settings.width, settings.height, bpp, SDL_HWSURFACE );
	if ( screen == NULL )
	{
		printf ( "Don't init resolution (%dx%d) : %s\n", settings.width, settings.height, SDL_GetError ( ) );
		return NULL;
	}

	SDL_WM_SetCaption ( "Engine: RT2", 0 );
	buf = static_cast<unsigned int *>(screen->pixels);
	SDL_UpdateRect ( screen, 0, 0, settings.width, settings.height);

	return buf;
}

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

		Scene scene;
		scene.load_from_file(settings.path_to_objfile);
		Engine engine(scene, InitSDL(settings));

		timer.Start();

		for (size_t i = 0; i < settings.count_frame; i++)
		{
			engine.rendering();

			if ( settings.file_write == true )
			{
				SDL_SaveBMP ( screen, string(Long::ToString(engine.get_num_frame(), 8) + ".bmp").c_str() );
			}
			std::cout << "\nframe [" << Long::ToString(engine.get_num_frame(), 5) << "] = " << Float::ToString(engine.get_fps(), 3) << " fps"; std::cout.flush();
			SDL_UpdateRect ( screen, 0, 0, settings.width, settings.height);
		}

		timer.Stop ();

		std::cout << "\n\nTotal time: " << timer << "\n";
	}
	catch (Exception & exception)
	{
		std::cout << "EXCEPTION: " << exception.what() << "n";
	}
	catch(...){}
	return 0;
}

