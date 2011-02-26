
#include <exception>

#include "mlib/console_parameters.hpp"

template <typename T>
T from_str(const std::string & str)
{
	T val;
	if (std::istringstream(str) >> val)
		return val;
	else
		throw std::exception();
}

template<>
std::string from_str(const std::string &str)
{
	return str;
}

#define SPECIALIZATION(TYPE)\
template<>\
TYPE ConsoleParameters::get(std::string param, TYPE def_value)\
{\
	int i = 0;\
\
	std::vector<std::string> params = get_aliases_from_string(param);\
\
	while (i < argc)\
	{\
		for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)\
		{\
			if ((*it).compare(argv[i]) == 0)\
			{\
				return from_str<TYPE>(argv[i+1]);\
			}\
		}\
		i++;\
	}\
	return def_value;\
}

SPECIALIZATION(int)
SPECIALIZATION(long)
SPECIALIZATION(double)
SPECIALIZATION(std::size_t)
SPECIALIZATION(std::string)

#define SPECIALIZATIONVEC(TYPE)\
template<>\
std::vector<TYPE> ConsoleParameters::get_vec(std::string param, TYPE def_value, int def_size_vector)\
{\
	int i = 0;\
\
	std::vector<std::string> params = get_aliases_from_string(param);\
\
	while (i < argc)\
	{\
		for (std::vector<std::string>::const_iterator it = params.begin(); it != params.end(); it++)\
		{\
			if ((*it).compare(argv[i]) == 0)\
			{\
				std::vector<TYPE> vector_value;\
\
				try\
				{\
					int j = 0;\
					while ( i + 1 + j < argc)\
					{\
						vector_value.push_back(from_str<TYPE>(argv[i + 1 + j]));\
						j++;\
					}\
				}\
				catch(...){}\
\
				return vector_value;\
			}\
		}\
		i++;\
	}\
	return std::vector<TYPE>(def_size_vector, def_value);\
}\

SPECIALIZATIONVEC(int)
SPECIALIZATIONVEC(long)
SPECIALIZATIONVEC(double)
SPECIALIZATIONVEC(std::string)
SPECIALIZATIONVEC(std::size_t)

bool ConsoleParameters::has(const std::string& param)
{
	int i = 0;
	while (i < argc)
	{
		bool compare = false;

		std::vector<std::string> params = get_aliases_from_string(param);

		for (std::vector<std::string>::iterator it = params.begin(); it != params.end(); it++)
			compare = compare || ((*it).compare(argv[i]) == 0);

		if (compare)
			return true;
		i++;
	}
	return false;
}

std::vector<std::string> ConsoleParameters::get_aliases_from_string(std::string aliases)
{
	std::size_t pos = aliases.find(" ");

	while (pos != std::string::npos)
	{
		aliases.erase(pos, 1);
		pos = aliases.find(" ");
	}

	aliases.append("|");
	pos = aliases.find("|");

	std::vector<std::string> als;

	while (pos != std::string::npos)
	{
		als.push_back(aliases.substr(0, pos));
		aliases.erase(0, pos + 1);
		pos = aliases.find("|");
	}

	return als;
}

int ConsoleParameters::count_args() const
{
	return argc;
}

std::string ConsoleParameters::get_path()
{
        return path;
}

std::string ConsoleParameters::operator [](const int index) const
{
	if (index < count_args())
		return argv[index];
	else
		throw std::exception();
}

std::ostream& operator << (std::ostream& out, const ConsoleParameters & params)
{
	for (int i = 0; i < params.count_args(); i++)
		out << i << ": " << params[i] << std::endl;
	out << std::endl;
	return out;
}

