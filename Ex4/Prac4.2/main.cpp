// Practice 4.2

#include <iostream>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;

template<class T>
struct test : mpl::bool_<false>
{
	BOOST_STATIC_ASSERT(0);
	///	typedef typename mpl::bool_<false> type;

};


template<class A1, class A2, class A3=mpl::bool_<false>, class A4=mpl::bool_<false>, class A5=mpl::bool_<false> >
struct logical_or :

	mpl::eval_if< A1
	,	mpl::bool_<true>
	,	typename mpl::eval_if< A2
	, mpl::bool_<true>
	,		typename mpl::eval_if< A3
	, mpl::bool_<true>
	,			typename mpl::eval_if< A4
	, mpl::bool_<true>
	,				typename mpl::eval_if< A5
	, mpl::bool_<true>
	, mpl::bool_<false>
	>
	>
	>
	>
	>
{

};



template<class A1, class A2>
struct logical_and :

	mpl::eval_if< A1
	,	typename mpl::eval_if< A2
	, mpl::bool_<true>
	, mpl::bool_<false>
	>
	,	mpl::bool_<false>
	>
{

};


void main()
{
	std::cout << "aa" << std::endl;

	if (logical_or< mpl::bool_<false>, mpl::bool_<false>, mpl::bool_<true>, test<int> >())
	{
		printf( "okok\n" );
	}

	//	bool r1 = boost::is_same< mpl::bool_<true>::type, mpl::bool_<true> >::value;

	// 	mpl::if_<
	// 		mpl::bool_<true>
	// 		, mpl::bool_<true>
	// 		, BOOST_STATIC_ASSERT(0)
	// 	>::type;

	// 	mpl::if_<
	// 		mpl::bool_<true>
	// 		, mpl::bool_<true>
	// 		, test<int> >::type a;


	if (logical_and< mpl::bool_<false>, test<int> >())
	{
		//test<int> a;
		printf( "okok\n" );
	}

}

