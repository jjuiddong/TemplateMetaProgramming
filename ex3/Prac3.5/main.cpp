// practice 3.5

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
using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;

struct add_ptr
{
	template<class T>
	struct apply
	{
		typedef T* type;
	};
};

// struct once
// {
// 	template<class F, class X>
// 	struct apply
// 	{
// 		typedef F::apply< X >::type type;
// 	};
// };

// F< F<X> >
template<class F, class X>
struct twice : 
	mpl::apply<
		F,
		typename mpl::apply<F, X>::type
	>
{
	// 	typedef typename F::apply< X >::type once;
	// 	typedef typename F::apply< once >::type type;

	// 	template<class F, class X>
	// 	struct apply
	// 	{
	// 		typedef typename F::apply< 
	// 			F::apply< X >::type >::type type;
	// 	};

	// 	typedef typename mpl::lambda< 
	// 		//typename mpl::lambda<F::apply, X>::type,
	// 		F,
	// 		X >::type type;

};

template<class T>
struct twoptr :
	twice<
	boost::add_pointer< _1 >
	,	T >
{};





void main()
{
	bool r1 = boost::is_same< 
		add_ptr::apply<int>::type
		,	int*
	>::value;

	bool r2 = boost::is_same<
		twoptr<int>::type
		,	int**
	>::value;

	// practice 3-3
	bool r3 = boost::is_same<
		twoptr< 
		typename twoptr<int>::type >::type
		,	int****
	>::value;

	// practice 3-4
	bool r4 = boost::is_same<

		typename twice<
			boost::add_pointer<_>,

			typename twice< 
				boost::add_pointer<_>
				, int >::type
		>::type

		,	int****
	>::value;

	// practice 3-5
	// 람다표현식이란 자리표를 포함한 메타함수를 뜻한다.
	bool r5 = boost::is_same<

	mpl::apply< 
		boost::add_pointer<_>
		, typename mpl::apply<
			boost::add_pointer<_>
			,int
			>::type
	>::type
	,	int**>::value;


}
