
/// SDL ///

#include <SDL/SDL.h>

SDL_Surface *screen;

#define bpp 32

//////////

#include <iostream>
#include <string>

#include "scene.hpp"
#include "light.hpp"
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
        unsigned int * buf = NULL;
        screen = NULL;

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

                //Timer timer;
                //std::cout << "\nCPU Frequency: " << timer.GetFrequency() << std::endl;
		std::cout.flush();

                vec4 cam_pos = vec4( 5.0f, 0.0f, 0.0f, 0.0f);

                Camera * camera = new Camera (cam_pos, 0.0f, 0.0f, 0.0f, settings.width, settings.height, 60.0f, settings.antialiasing);

                camera->rotate_y(45);
                camera->move(vec4(5.0f, 4.0f, -5.0f, 0.0f));

                // set lights

                Light * lights = new Light[settings.lights];
                for (size_t i = 0; i < settings.lights; i++)
                {
                        float intens = 1.0f / static_cast<float>(settings.lights);
                        lights[i].set(vec4(6.0f, 15.0f, 6.0f - 0.5f * (i * intens), 0.0f), intens);
                }

                Scene * scene = new Scene(camera, lights, settings.lights);
                scene->SetMaxCountObjectsInBVH(settings.max_count_objects_in_bvh);
                //timer.Start();
                scene->load_from_file(settings.path_to_objfile);
                //timer.Stop();
                std::cout << "Time build BVH: ";
                //<< timer.GetTotalTimeInMSeconds() << "ms \n";
                std::cout.flush();
                //timer.Reset();

		Engine engine(scene, InitSDL(settings));
                engine.set_threads(settings.threads);                
                engine.set_depth(settings.depth);

                //timer.Start();

                SDL_Event event;
                bool exit = false;

                for (size_t i = 0; i < settings.count_frame; i++)
		{
                        /*/
                        while (SDL_PollEvent(&event))
                        {
                                switch( event.type )
                                {
                                        case SDL_KEYDOWN:
                                                switch( event.key.keysym.sym )
                                                {
                                                        case SDLK_w:
                                                                camera->rotate_x(1);
                                                        break;
                                                        case SDLK_q:
                                                                camera->rotate_x(-1);
                                                        break;

                                                        case SDLK_a:
                                                                camera->rotate_y(1);
                                                        break;
                                                        case SDLK_s:
                                                                camera->rotate_y(-1);
                                                        break;

                                                        case SDLK_z:
                                                                camera->rotate_z(1);
                                                        break;
                                                        case SDLK_x:
                                                                camera->rotate_z(-1);
                                                        break;

                                                        case SDLK_UP:
                                                                cam_pos(0, cam_pos[0] + 0.1f);
                                                        break;
                                                        case SDLK_DOWN:
                                                                cam_pos(0, cam_pos[0] - 0.1f);
                                                        break;

                                                        case SDLK_LEFT:
                                                                cam_pos(1, cam_pos[1] + 0.1f);
                                                        break;
                                                        case SDLK_RIGHT:
                                                                cam_pos(1, cam_pos[1] - 0.1f);
                                                        break;

                                                        case SDLK_LESS:
                                                                cam_pos(2, cam_pos[2] + 0.1f);
                                                        break;
                                                        case SDLK_GREATER:
                                                                cam_pos(2, cam_pos[2] - 0.1f);
                                                        break;

                                                        case SDLK_ESCAPE:
                                                                exit = true;
                                                        break;

                                                        default:
                                                        break;
                                                }
                                        break;
                                }
                        }
                        camera->move(cam_pos);
                        //*/

			engine.rendering();

			if ( settings.file_write == true )
			{
				SDL_SaveBMP ( screen, string(Long::ToString(engine.get_num_frame(), 8) + ".bmp").c_str() );
			}
                        std::cout << "\nframe [" << Long::ToString(engine.get_num_frame(), 5) << "] = " << Float::ToString(engine.get_fps(), 3) << " fps"; std::cout.flush();
			SDL_UpdateRect ( screen, 0, 0, settings.width, settings.height);
                        if (exit == true) break;
		}

                //timer.Stop ();

                //std::cout << "\n\nTotal time: " << timer;
                std::cout << "\n";
	}
	catch (Exception & exception)
	{
		std::cout << "EXCEPTION: " << exception.what() << "n";
	}
	catch(...){}

        SDL_FreeSurface(screen);

	return 0;
}

