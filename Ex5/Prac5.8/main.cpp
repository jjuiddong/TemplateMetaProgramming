// practice 5-8

#include <iostream>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/multiplies.hpp>

#include <boost/mpl/at.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/size.hpp>


using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;


struct fibo_tag {};
struct fibo_series
{
	typedef fibo_tag tag;
	typedef fibo_series type;
};

template <int Value, int Pos>
struct fibo_iterator
{
	typedef fibo_tag tag;
	typedef typename fibo_iterator type;
	static const int value = Value;
	static const int pos = Pos;
};

template<int N>
struct fibo_val
{
	static const int value = 
		fibo_val<N-1>::value + 
		fibo_val<N-2>::value;
};

template<>
struct fibo_val<0> : mpl::int_<0>
{};

template<>
struct fibo_val<1> : mpl::int_<1>
{};


namespace boost { namespace mpl {
	template<>
	struct begin_impl< fibo_tag >
	{
		template<class S>
		struct apply
		{
			typedef typename fibo_iterator<0,0> type;
		};
	};
}}


namespace boost { namespace mpl {
	template<>
	struct advance_impl< fibo_tag >
	{
		template<class It, class N>
		struct apply
		{
			typedef typename fibo_iterator< 
				fibo_val< It::pos + N::value >::value
				, It::pos + N::value > type;
		};
	};
}}


namespace boost { namespace mpl {
	template<int Value, int PosValue>
	struct deref< fibo_iterator<Value, PosValue> >
	{
		typedef typename fibo_iterator<Value, PosValue> type;
	};
}}

// 0 1 1 2 3 5 8 13 21..
//fibonacci_series
// typedef mpl::advance_c< mpl::begin< fibon >::type, 6 >::type i;
// mpl::deref<i>:;type::value == 8

// typedef mpl::advance_c< i, 4 >::type j;
// mpl::deref<j>::type::value == 55

typedef mpl::advance_c< 
	mpl::begin< fibo_series >::type, 6 
	>::type i;
BOOST_STATIC_ASSERT( mpl::deref<i>::type::value == 8 );

typedef mpl::advance_c< i, 4>::type j;
BOOST_STATIC_ASSERT( mpl::deref<j>::type::value == 55 );


void main()
{
	int n = mpl::deref<i>::type::value;

}
