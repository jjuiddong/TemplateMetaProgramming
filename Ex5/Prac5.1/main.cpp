// practice 5.1

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


using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;

struct none {};

template<class T=none>
struct wrapAssert : T
{
	typedef typename T type;
	BOOST_STATIC_ASSERT(0);
};


template<class T0, class T1, class T2, class T3>
struct double_half
{
	typedef typename mpl::vector_c<int
		, T0::value*2
		, T1::value*2
		, T2::value
		, T3::value
	> type;
};


template<class Sequence>
struct double_first_half
{
	typedef typename double_half<
		typename mpl::at<Sequence, mpl::int_<0> >::type
		, typename mpl::at<Sequence, mpl::int_<1> >::type
		, typename mpl::at<Sequence, mpl::int_<2> >::type
		, typename mpl::at<Sequence, mpl::int_<3> >::type
	>::type type;
	
};

struct test1 :
	mpl::eval_if< 
		mpl::equal<
			double_first_half< mpl::vector_c<int,1,2,3,4> >::type
			, mpl::vector_c<int,2,4,3,4>
		>
	, none
	, wrapAssert<>
	>
{};


void main()
{
	int a = mpl::at< mpl::vector_c<int, 1,2,3,4>
		, mpl::int_<2> >::type::value;

	int b = mpl::integral_c<int,2>::value;

}