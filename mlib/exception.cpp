
#include "mlib/exception.hpp"
#include "mlib/long.hpp"

namespace mlib
{
	Exception::Exception(std::string message, std::string file, long line)
	{
		msg = "Error (" + file + ":" + Long::ToString(line, 3) + ") : " + message; 
	}

	std::string Exception::what()
	{
		return msg;
	}
}

