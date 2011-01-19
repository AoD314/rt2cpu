
#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <exception>
#include <string>

namespace mlib
{
	class Exception : public std::exception
	{
		private:
			std::string msg;

		public:
			Exception(std::string message, std::string file, long line);
			std::string what();

			~Exception() throw () {}
	};

}

#define Error ( msg ) throw Exception ( msg , __FILE__, __LINE__ )

#endif

