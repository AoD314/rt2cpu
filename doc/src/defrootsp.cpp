template <size_t N, size_t Mid>
struct Root<N, Mid, Mid>
{
	static const size_t ret = Mid;
};
