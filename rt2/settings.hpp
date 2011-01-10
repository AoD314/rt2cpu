
#ifndef __SETTINGS_HPP__
#define __SETTINGS_HPP__

#include <string>

class Settings
{
    private:
        void print_help();
    public:
        int lights;
        int depth;
        int threads;
        int width;
        int height;

        std::string path_to_objfile;

        bool benchmark_mode;
        bool active_event;
        bool file_write;
        bool quiet_mode;
        size_t count_frame;
        size_t depth_bvh;

        bool is_exit;

        Settings(int argc, char ** argv);
        void print_params();

};

#endif
