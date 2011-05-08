template <size_t N, size_t Low=1, size_t Upp=N>
struct Root
{
	static const size_t calc = (Low+Upp)/2;
	static const bool   test = ((calc*calcc)>=N);
	static const size_t ret  = Root<N,(test?Low:calc+1),(test?calc:calcUpp)>::ret;
};
