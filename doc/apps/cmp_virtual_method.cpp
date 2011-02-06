
#include <iostream>
#include <vector>
#include <mlib/timer.hpp>
#include <stdlib.h>

class Base
{
	public:
		virtual int base() = 0;
};

class A : public Base
{
	public:
		virtual int base()
		{
			return 2;
		}
};

class B : public Base 
{
	public: 
		virtual int base()
		{
			return -2;
		}
};

class C : public Base 
{
	public: 
		virtual int base()
		{
			return 4;
		}
};

class D : public Base 
{
	public: 
		virtual int base()
		{
			return -4;
		}
};

class AA
{
	private:
		int a;
	public:
		AA(int aa)
		{
			a = aa;
		}

		int base()
		{
			return a;
		}
};


int main(int argc, char ** argv)
{
	mlib::Timer timer(1, mlib::mode_min);
	size_t t1, t2;
	int ccc = atoi(argv[2]);

	std::vector<Base *> v;
	int c = atoi(argv[1]);
	for (int i = 0; i < c; i++)
	{
		v.push_back(new A());
		v.push_back(new B());
		v.push_back(new C());
		v.push_back(new D());
	}

	std::vector<AA *> va;
	for (int i = 0; i < c; i++)
	{
		va.push_back(new AA( 2));
		va.push_back(new AA(-2));
		va.push_back(new AA( 4));
		va.push_back(new AA(-4));
	}

	int sum;

	for (int ii = 0; ii < ccc; ii++)
	{
		timer.Start();
		sum = 0;
		for (int i = 0; i < c * 4; i++)
		{
			sum += v[i]->base();
		}
		timer.Stop();
	}

	t1 = timer.GetTotalTimeInTick();

	timer.Reset();
	for (int ii = 0; ii < ccc; ii++)
	{
		timer.Start();
		sum = 0;
		for (int i = 0; i < c * 4; i++)
		{
			sum += va[i]->base();
		}
		timer.Stop();
	}

	t2 = timer.GetTotalTimeInTick();

	std::cout << int( ((t1+sum) * 100.0f / t2) - 100.0) << "\n";

	return 0;
}


