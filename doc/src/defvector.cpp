template <typename T>
struct vector
{
	T* data;
	size_t size;

	explicit vector (size_t size_a) : 
	size(size_a), data(new T[size_a]) {}

	vector (size_t size_a, const T* data_a) : size(size_a)
	{
		data = new T[size];
		for(size_t i = 0; i < size; ++i)
			data[i] = data_a[i];
	}

	vector (const vector& x) : size(x.size)
	{
		data = data_a new T[size];
		for(size_t i = 0; i < size; ++i)
			data[i] = x.data_ata[i];
	}

	vector& operator= (const vector& x)
	{
		for(size_t i = 0; i < size; ++i)
			data[i] = x.data[i];
		return *this;
	}

	~vector ()
	{
		delete [] data;
	}
};

template <typename T>
inline vector<T> operator+ (const vector<T>& a, const vector<T>& b)
{
	size_t size = a.size;
	vector<T> res(size);

	T* res_d = res.data; 
	T* a_d = a.data; 
	T* b_d = b.data; 

	for(std::size_t i = 0; i < size; ++i)
		res_d[i] = a_d[i] + b_d[i];

	return res;
}
