
template <bool b, std::size_t i, std::size_t j>
class IFThenElse {};

template <std::size_t i, std::size_t j>
class IFThenElse < true, i, j>
{
public:
    enum { ret = i };
};

template <std::size_t i, std::size_t j>
class IFThenElse < false, i, j>
{
public:
    enum { ret = j };
};

template <bool b, typename T1 , typename T2>
class IFThenElseT {};

template<typename T1 , typename T2>
class IFThenElseT<true, T1, T2>
{
public:
    typedef T1 result;
};

template<typename T1 , typename T2>
class IFThenElseT<false, T1, T2>
{
public:
    typedef T2 result;
};
