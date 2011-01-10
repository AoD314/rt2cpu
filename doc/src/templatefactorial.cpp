template <int n>
struct factorial
{
	enum { ret = factorial<n-1>::ret * n};
};

template <>
struct factorial<0>
{
	enum { ret = 1};
};
