
#ifndef _LOGGER_HPP
#define	_LOGGER_HPP

#include <iostream>


namespace mlib
{
    class Logger
    {
        public:
            template <typename T>
            void Log(const T & t);

            template <typename T>
            void LogLn(const T & t);
    };

    class ConsoleLogger : public Logger
    {
        public:
            template <typename T>
            void Log(const T & t)
            {
                std::cout << t;
            }

            template <typename T>
            void LogLn(const T & t)
            {
                std::cout << t << std::endl;
            }
    };

    class EmptyLogger : public Logger
    {
        public:
            template <typename T> void Log(const T & t);
            template <typename T> void LogLn(const T & t);
    };

}

#endif

