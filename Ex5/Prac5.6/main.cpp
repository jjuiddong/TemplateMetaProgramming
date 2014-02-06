// practice 5-6

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



template<class T> struct dim
{
	BOOST_STATIC_ASSERT(0);
};

template<class A, int N1, int N2, int N3>
struct dim< A[N1][N2][N3] > :
	mpl::vector_c<int, N1, N2, N3>
{
	typedef typename A value_type;
};


template < class T >
struct dimensions :
	dim<T>::type
{};


struct test : 
	dimensions< float[10][5][3] >
{

};

// dimensions seq<array>
//size<seq>
//at_c<seq,0>::type::value
typedef dimensions< char[10][9][8] > seq;
BOOST_STATIC_ASSERT( mpl::size<seq>::value == 3 );

//BOOST_STATIC_ASSERT( mpl::at<seq, mpl::int_<0> >::type::value );
// BOOST_STATIC_ASSERT( 
// 		mpl::at<
// 		mpl::vector_c<int, 10,1,2>
// 		, mpl::int_<0>
// 		>::type::value == 10 );

struct none{};

template<class T=int>
struct wrapAssert : T
{
	typedef typename T type;
	BOOST_STATIC_ASSERT(0);
};

struct test2 :
	mpl::eval_if< 
		mpl::equal< 
			mpl::at<seq, mpl::int_<0> >::type
			, mpl::int_<10>
		>
		, none
		, wrapAssert<>
	>
{};

struct test3 :
	mpl::eval_if< 
	mpl::equal< 
	mpl::at<seq, mpl::int_<1> >::type
	, mpl::int_<5>
	>
	, none
	, wrapAssert<>
	>
{};

struct test4 :
	mpl::eval_if< 
	mpl::equal< 
	mpl::at<seq, mpl::int_<2> >::type
	, mpl::int_<3>
	>
	, none
	, wrapAssert<>
	>
{};

struct test5 :
	mpl::push_back< seq >::type
{};


void main()
{
// 	int n1 = test::type::n1;
// 	int n2 = test::type::n2;
//	test::type::value_type a;

}
