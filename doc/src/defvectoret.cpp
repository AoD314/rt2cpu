template <typename T>
struct vector
{
	T* data;
	size_t size;

	explicit vector (size_t size_a) : 
	size(size_a), data(new T[size_a]) {}

	inline vector (size_t size_a, const T* data_a)
	: size(size_a)
	{
		data = new T[size];
		for(size_t i = 0; i < size; ++i)
			data[i] = data_a[i];
	}

	inline vector (const vector& x) : size(x.size)
	{
		data = new T[size];
		for(size_t i = 0; i < size; ++i)
			data[i] = x.data[i];
	}

	inline vector& operator= (const vector& x)
	{
		for(size_t i = 0; i < size; ++i)
			data[i] = x.data[i];
		return *this;
	}

	inline const T& operator[] (size_t i) const
	{
		return data[i];
	}

	inline T& operator[] (size_t i)
	{
		return data[i];
	}

	template<typename Left, typename Op, typename Right>
	inline void operator= (const X<T,Left,Op,Right>& expr)
	{
		size_t size = this->size;
		for (size_t i = 0; i < size; ++i)
			data[i] = expr[i];
	}

	~vector ()
	{
		delete [] data;
	}
};
