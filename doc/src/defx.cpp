template<typename T, typename Left, typename Op, typename Right>
struct X
{
	X(Left t1, Right t2)
	: leftNode_(t1), rightNode_(t2) {}

	T operator[] (int i) const
	{
		Op op_;
		return op_.apply(leftNode_[i], rightNode_[i]);
	}

private:
	const Right rightNode_;
	const Left  leftNode_;
};

template
<
	typename T, 
	typename Left1, typename Op1, typename Right1,
	typename Left2, typename Op2, typename Right2
>
inline X<T, X<T, Left1, Op1, Right1>, plus<T>, X<T, Left2, Op2, Right2> >
operator + 
(
	const X<T, Left1, Op1, Right1>& a,
	const X<T, Left2, Op2, Right2>& b
)
{
	return  X<T, 
				X<T, Left1, Op1, Right1>, 
				plus<T>, 
				X<T, Left2, Op2, Right2> 
			>(a, b);
}

template<typename Left, typename T>
inline X<T, Left, plus<T>, const T*> 
operator + (const Left& a, const vector<T>& b)
{
	return X<T, Left, plus<T>, const T*>(a, b.data);
}

template<typename Right, typename T>
inline X<T, const T*, plus<T>, Right> 
operator + (const vector<T>& a, const Right& b)
{
	return X<T, const T*, plus<T>, Right>(a.data, b);
}

template<typename T>
inline X<T, const T*, plus<T>, const T*> 
operator + (const vector<T>& a, const vector<T>& b)
{
	return X<T, const T*, plus<T>, const T*>(a.data, b.data);
}
