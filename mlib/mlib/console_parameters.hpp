
#ifndef __CLPARAMS_HPP__
#define __CLPARAMS_HPP__

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

class ConsoleParameters
{
    private:
        int argc;
        char ** argv;
        std::vector<std::string> get_aliases_from_string(std::string aliases);

    public:
        ConsoleParameters(int argc, char ** argv): argc(argc), argv(argv){}

        bool has(const std::string& param);

        template <typename T>
        T get(std::string param, T def_value = T());

        template <typename T>
        std::vector<T> get_vec(std::string param, T def_value = T(), int def_size_vector = 1);

        int count_args() const;
        std::string operator [](const int index) const;
};

std::ostream& operator << (std::ostream& out, const ConsoleParameters & params);

#endif

