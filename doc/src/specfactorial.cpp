template <>
struct factorial<0>
{
	enum { ret = 1};
};
