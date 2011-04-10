
#include <iostream>
#include "settings.hpp"

#include <mlib/console_parameters.hpp>

Settings::Settings (int argc, char ** argv)
{
        ConsoleParameters params(argc, argv);

        lights   = params.get("--lights  | -l", 2);
        depth    = params.get("--depth   | -d", 2);
        threads  = params.get("--threads | -t", 12);
        width    = params.get("--width   | -w", 512);
        height   = params.get("--height  | -h", 512);

        antialiasing = params.get("--antialiasing | -a ", 4);

        count_frame              = params.get<size_t>("--frame  | -f",  3);
        max_count_objects_in_bvh = params.get<size_t>("--bvhobj | -bo", 8);

        benchmark_mode = params.has("--benchmark | -b");
        active_event   = params.has("--event     | -e");
        file_write     = params.has("--saveimg   | -s");
        quiet_mode     = params.has("--quiet     | -q");

        //path_to_objfile = params.get<std::string>("--obj | -o", "../data/my_obstrakt.obj");
        //path_to_objfile = params.get<std::string>("--obj | -o", "../data/my_sharHQ.obj");
        path_to_objfile = params.get<std::string>("--obj | -o", "../data/my_stul2.obj");

        is_exit = false;

        if (params.has(" --help | --usage "))
        {
                is_exit = true;
                print_help();
        }
        else
                if (params.has("--print | -p"))
                        print_params();
}

void Settings::print_params()
{
        std::cout << "Console Parameters:";
        std::cout << "\nResolution                     : " << width << "x" << height;
        std::cout << "\nCount threads                  : " << threads;
        std::cout << "\nAntialiasing                   : " << antialiasing;
        std::cout << "\nDepth ray tracing              : " << depth;
        std::cout << "\nMax count objects in BVH tree  : " << max_count_objects_in_bvh;
        std::cout << "\nCount lights                   : " << lights;
        std::cout << "\nCount frames                   : " << count_frame;

        std::cout << "\nPath to objfile                : " << path_to_objfile;
        std::cout << "\nbenchmark                      : " << ((benchmark_mode == true) ? "true" : "false");
        std::cout << "\nquiet                          : " << ((quiet_mode == true)     ? "true" : "false");
        std::cout << "\nsaveimg                        : " << ((file_write == true)     ? "true" : "false");
        std::cout << "\nevent                          : " << ((active_event == true)   ? "true" : "false");

        std::cout << std::endl;
}

void Settings::print_help()
{
        std::cout << "Real Time Ray Tracing on CPU";
        std::cout << "\n\nHelp:";
        std::cout << "\n\t--help, --usage       - Help informations (this text)";
        std::cout << "\n\t--width        <int>(-w)  - Width image";
        std::cout << "\n\t--height       <int>(-h)  - Height image";
        std::cout << "\n\t--frame        <int>(-f)  - Count frame before exit";
        std::cout << "\n\t--threads      <int>(-t)  - Count threads in OpenMP or TBB";
        std::cout << "\n\t--antialiasing <int>(-a)  - Antialiasing";
        std::cout << "\n\t--depth        <int>(-d)  - Depth of ray tracing";
        std::cout << "\n\t--bvhobj       <int>(-bo) - Max count objects in BVH tree";
        std::cout << "\n\t--lights       <int>(-l)  - Count lights";
        std::cout << "\n\t--obj          <str>(-o)  - Path to obj file (object for render)";
        std::cout << "\n\t--print        (-p)      - Print parameters";
        std::cout << "\n\t--benchmark    (-b)      - Benchmark";
        std::cout << "\n\t--quiet        (-q)      - No output";
        std::cout << "\n\t--saveimg      (-s)      - Save image to file";
        std::cout << "\n\t--event        (-e)      - Event";
        std::cout << std::endl;
}

