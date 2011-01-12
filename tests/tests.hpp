
#include <iostream>
#include <string>
#include <iomanip>

void print_result ( bool res, std::string nametest , size_t & total_tests, size_t & total_good_tests )
{
	total_tests++;

	nametest = nametest + " ";
	std::cout.setf ( std::ios::left );
	std::cout << std::setw ( 65 ) << std::setfill ( '.' ) << nametest;

	if ( res == true )
	{
		std::cout << "\033[0;32m" << " pass";
		total_good_tests++;
	}
	else
		std::cout << "\033[0;31m" << " fail";

	std::cout << "\033[0m";
	std::cout << std::endl;
}

/*
30m - black
31m - red
32m - green
33m - yellow
34m - blue
35m - pink
36m - cyan
37m - white
*/
