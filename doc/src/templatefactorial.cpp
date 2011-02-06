template <int n>
struct factorial
{
	enum { ret = factorial<n-1>::ret * n};
};
