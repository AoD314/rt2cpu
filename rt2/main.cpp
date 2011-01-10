
#include <omp.h>

/// SDL ///
#include <SDL/SDL.h>
SDL_Surface *screen;
#define bpp 32
//////////

#include <mlib/fixed_vector.hpp>
#include <mlib/processor.hpp>
#include <mlib/minmax.hpp>
#include <mlib/integer.hpp>
#include <mlib/objfile.hpp>
#include <mlib/long.hpp>
#include <mlib/double.hpp>
#include <mlib/timer.hpp>
#include <mlib/randomize.hpp>
using namespace mlib;


#include <iostream>
#include <string>
using namespace std;

#include "camera.hpp"
#include "scene.hpp"
#include "engine.hpp"

using namespace engine;
using namespace scene;
using namespace camera;

#include "settings.hpp"

int main ( int argc, char ** argv )
{
    try
    {
        Rand::Randomize();

        Settings settings(argc, argv);
        if (settings.is_exit) return 0;

        settings.print_params();

        Timer timer;
        
        std::cout << "\nCPU Frequency: " << timer.GetFrequency() << std::endl;
        std::cout.flush();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        // init camera

        vec4 cam_pos(3.0f , 0.0f , 2.0f , 0.0f);
        vec4 cam_dir(0.0f , 0.0f , 0.0f , 0.0f);
        vec4 cam_upd(3.0f , 0.0f , 3.0f , 0.0f);

        Camera cam (cam_pos, cam_dir, cam_upd, settings.width, settings.height, 3.14159265f / 3.0f);

        // material

        vec4 mat_amb(0.15f , 0.15f , 0.15f , 0.0f);
        vec4 mat_spc(0.75f , 0.75f , 0.75f , 0.0f);
        vec4 mat_dif(0.95f , 0.95f , 0.95f , 0.0f);
        vec4 mat_rf2(0.35f , 0.35f , 0.35f , 0.0f);

        vec4 Red(1, 1, 1, 0);
        TextureColor tcred(Red);
        MaterialSimple mtrRed;
        mtrRed.AddTexture(&tcred);
        mtrRed.SetColor(mat_amb, mat_dif, mat_spc, mat_rf2, 32);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::cout << "\nCreating scene ... ";
        std::cout.flush();

        scene::Scene sc(cam);

        std::cout << "done. ";
        std::cout.flush();

        std::cout << "\nLoading " << settings.path_to_objfile << " ... ";

        Objfile objfile;
        objfile.read (settings.path_to_objfile);

        std::cout << "done\nCount triangles: " << objfile.GetCountTriangle ();
        std::cout.flush ();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        sc.allocate_p ( objfile.GetCountTriangle () + 1 );

        vec4 v0,v1,v2, n;
        Triangle * tr = new_memory<Triangle> (objfile.GetCountTriangle ());

        for (std::size_t i = 0; i < objfile.GetCountTriangle (); i++)
        {
                v0 = objfile.GetPointInTriangle (i, 0);
                v1 = objfile.GetPointInTriangle (i, 1);
                v2 = objfile.GetPointInTriangle (i, 2);
                n  = objfile.GetNormalForTriangle (i);
                tr[i].SetCoordinate (v0,v1,v2);
                tr[i].SetMaterial (&mtrRed);
                tr[i].SetNormal (n);

                sc.AddPrimitives (&tr[i]);
        }

        std::cout << "\nProgress: 100%";
        std::cout.flush ();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        vec4 light01_a (0.05f/(float)settings.lights , 0.05f/(float)settings.lights , 0.05f/(float)settings.lights , 0.0f);
        vec4 light01_s (1.00f/(float)settings.lights , 1.00f/(float)settings.lights , 1.00f/(float)settings.lights , 0.0f);
        vec4 light01_d (1.00f/(float)settings.lights , 1.00f/(float)settings.lights , 1.00f/(float)settings.lights , 0.0f);

        vec4 light_pos;

        for (int i = 0; i < settings.lights; i++)
        {
                Lights * ln  = new_memory<Lights>(1);
                light_pos.set(6.0f, (2.0f * (float)i/(float)settings.lights) - 1.0f, 6.0f, 0.0f);
                light_pos.set(4.0f, 4.0f, 0.0f, 0.0f);
                ln[0].settings(light_pos, light01_a, light01_s, light01_d);
                sc.AddLight (ln);
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// init SDL ///

        unsigned int * buf ; //= new uint32_t[width * height];

        if ( (SDL_Init ( SDL_INIT_VIDEO )) < 0 )
        {
                printf ( "Don't init SDL: %s\n", SDL_GetError ( ) );
                return false;
        }

        screen = SDL_SetVideoMode ( settings.width, settings.height, bpp, SDL_HWSURFACE );
        if ( screen == NULL )
        {
                printf ( "Don't init resolution (%dx%d) : %s\n", settings.width, settings.height, SDL_GetError ( ) );
                return false;
        }

        SDL_WM_SetCaption ( "Engine: RT2", 0 );
        buf = ( Uint32* ) screen->pixels;
        SDL_UpdateRect ( screen, 0, 0, settings.width, settings.height);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // BVH                                                                                                            //
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        std::cout << "\nBuilding BVH tree ... ";
        std::cout.flush ();

        timer.Start ();
        sc.GenBVH ();
        timer.Stop ();

        std::cout << "done. (" << std::fixed << std::setprecision(10) << timer.GetTimeInSeconds() << " sec)";
        std::cout.flush ();

        timer.Reset ();

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        EngineRT2 rt2(sc, buf, true);

        rt2.SetDepth   (settings.depth);
        rt2.SetThreads (settings.threads);
        rt2.SetParts   (1);

        std::cout << "\nRendering ... ";
        std::cout.flush ();

        timer.Start ();

        for (std::size_t i = 0; i < settings.count_frame; i++)
        {
                rt2.Rendering (1);

                SDL_UpdateRect ( screen, 0, 0, settings.width, settings.height);

                if ( settings.file_write == true )
                {
                        string namefile = Long::ToString(rt2.CountFrame(), 8) + ".bmp";
                        SDL_SaveBMP ( screen, namefile.c_str() );
                }

                timer.Stop ();
                std::cout << "\nframe: " << i << " time: " << timer.GetTimeInSeconds () << " sec";
                timer.Start();
        }

        timer.Stop ();

        std::cout << "\n\nTotal time: " << timer << "\n";
    }
    catch (...){}
    return 0;
}

