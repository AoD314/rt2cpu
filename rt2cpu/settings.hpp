
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
        int antialiasing;
        int width;
        int height;
	int max_count_objects_in_bvh;

        std::string path_to_objfile;

        bool benchmark_mode;
        bool active_event;
        bool file_write;
        bool quiet_mode;
        size_t count_frame;

        bool is_exit;

        Settings(int argc, char ** argv);
        void print_params();

};

#endif

