
#include "mlib/objfile.hpp"
#include <iostream>

namespace mlib
{
	Objfile::Objfile ()
	{
	}

	Objfile::Objfile (const std::string & filename)
	{
		read( filename );
	}

	bool Objfile::read (const std::string & filename)
	{
		std::ifstream infile;
		infile.open(filename.c_str ());

		if (infile.is_open())
		{
			std::string str = "";

			std::valarray<int>   vi(3);
			std::valarray<float> vf(3);

			while ( ! infile.eof() )
			{
				infile >> str;

				if (str == "v")
				{
					infile >> vf[0] >> vf[1] >> vf[2];
					v.push_back( vf );
				}
				else if (str == "vn")
				{
					infile >> vf[0] >> vf[1] >> vf[2] ;
					v.push_back( vf );
				}
				else if (str == "f")
				{
					int t; char c;
					infile	>> vi[0] >> c >> c >> t;
					infile	>> vi[1] >> c >> c >> t;
					infile	>> vi[2] >> c >> c >> t;
					f.push_back(vi);
					fn.push_back (t);
				}
			}
		}
		else
		{
			std::cout << "\nError: file " << filename << " not found !!!\n";
		}
		infile.close();
		return true;
	}

	vec4 Objfile::GetPointInTriangle(size_t num_triangle, size_t num_vertex)
	{
		num_vertex = num_vertex % 3;

		std::valarray<float> tmp = v.at(f.at(num_triangle)[num_vertex] - 1);

		return vec4(tmp[0], tmp[1], tmp[2], 0.0f);
	}

	vec4 Objfile::GetNormalForTriangle (size_t num_triangle)
	{
		std::valarray<float> tmp = v.at(fn.at(num_triangle));

		return vec4(tmp[0], tmp[1], tmp[2], 0.0f);
	}

	size_t Objfile::GetCountTriangle()
	{
		return f.size();
	}
}

