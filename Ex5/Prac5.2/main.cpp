// practice 5-2
// practice 5-3
// practice 5-4
// practice 5-5

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


using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;



struct none {};
struct tiny_tag {};

template<class T0=none, class T1=none, class T2=none>
struct tiny
{
	typedef typename tiny_tag tag;
	typedef tiny type;	
	typedef typename T0 t0;
	typedef typename T1 t1;
	typedef typename T2 t2;
};

template<class Tiny, class Pos>
struct tiny_iterator
{
	typedef typename tiny_tag tag;
	typedef typename Pos value;
	typedef typename Tiny Sequence;
};

namespace boost { namespace mpl {
	template<class S, class Pos>
	struct next< tiny_iterator<S,Pos> >
	{
		typedef typename tiny_iterator<S,
			mpl::int_<Pos::value+1 > > type;
	};
}}

namespace boost { namespace mpl {
	template<class S, class N>
	struct prior< tiny_iterator<S,N> >
	{
		typedef typename tiny_iterator<S,
			mpl::int_<N::value-1> > type;
	};
}}

namespace boost { namespace mpl {
	template<>
	struct begin_impl<tiny_tag>
	{
		template <class S>
		struct apply
		{
			typedef typename tiny_iterator<S,mpl::int_<0> > type;		
		};
	};
}}

namespace boost { namespace mpl {
	template<>
	struct clear_impl<tiny_tag>
	{
		template <class S>
		struct apply :
			tiny<none,none,none>
		{};
	};
}}


template<class S, class T1, int N>
struct tiny_push_front;

template<class S, class T1>
struct tiny_push_front<S, T1, 0> :
	tiny<T1,none,none>
{};

template<class S, class T1>
struct tiny_push_front<S, T1, 1> :
	tiny<T1,typename S::t0,none>
{};

template<class S, class T1>
struct tiny_push_front<S, T1, 2> :
	tiny<T1,typename S::t0, typename S::t1>
{};

template<class S, class T1>
struct tiny_push_front<S, T1, 3>
{
	BOOST_STATIC_ASSERT(0);
};


template<class Tiny, class Pos>
struct tiny_at;

template<class Tiny>
struct tiny_at<Tiny, mpl::int_<0> >
{
	typedef typename Tiny::t0 type;
};
template<class Tiny>
struct tiny_at<Tiny, mpl::int_<1> >
{
	typedef typename Tiny::t1 type;
};
template<class Tiny>
struct tiny_at<Tiny, mpl::int_<2> >
{
	typedef typename Tiny::t2 type;
};
template<class Tiny>
struct tiny_at<Tiny, mpl::int_<3> >
{
	//	BOOST_STATIC_ASSERT(0);
	typedef typename none type;
};



// template<class S, class It>
// struct tiny_at
// {
// 	typedef typename tiny_at<S, typename It::value >::type type;	
// };

template<class S, class N>
struct tiny_advance
{
	typedef typename tiny_at< S, tiny_iterator<S, N> >::type type;
};





namespace boost { namespace mpl {
	template<>
	struct at_impl<tiny_tag>
	{
		template<class S, class It>
		struct apply : tiny_at<S, typename It::value >
		{};
	};
}}

namespace boost { namespace mpl {
	template<>
	struct advance_impl<tiny_tag>
	{
		template<class It, class N>
		struct apply : 
			tiny_at< typename It::Sequence, 
			mpl::int_<N::value + It::value::value> >
		{};
	};
}}







template<class It>
struct tiny_deref
{
	typedef typename tiny_at< typename It::Sequence, It >::type type;
};


template<class S>
struct tiny_size;

template<>
struct tiny_size< tiny<none, none, none> > :
	mpl::int_<0>
{};

template<class T0>
struct tiny_size< tiny<T0, none, none> >:
	mpl::int_<1>
{};

template<class T0, class T1>
struct tiny_size< tiny<T0, T1, none> >:
	mpl::int_<2>
{};

template<class T0, class T1, class T2>
struct tiny_size< tiny<T0, T1, T2> >:
	mpl::int_<3>
{};

namespace boost { namespace mpl {
	template<>
	struct end_impl< tiny_tag >
	{
		template<class S>
		struct apply			
		{
			typedef typename tiny_iterator<S, tiny_size<S> > type;
		};
	};
}}


namespace boost { namespace mpl {

	template<class S, class Pos>
	struct deref< tiny_iterator<S,Pos> > :
		mpl::at< S, typename tiny_iterator<S,Pos> >
	{};

}}


template<class S, class T, int N> 
struct tiny_push_back
{
	BOOST_STATIC_ASSERT(0);
};

template<class S, class T>
struct tiny_push_back<S,T,0> : tiny<T>
{};

template<class S, class T>
struct tiny_push_back<S,T,1> : tiny<typename S::t0,T>
{};

template<class S, class T>
struct tiny_push_back<S,T,2> : tiny<typename S::t0, typename S::t1, T>
{};



template<class S, int N> 
struct tiny_pop_front
{
	BOOST_STATIC_ASSERT(0);
};

template<class S>
struct tiny_pop_front<S,0> : tiny<none, none, none>
{};

template<class S>
struct tiny_pop_front<S,1> : tiny<none,none,none>
{};

template<class S>
struct tiny_pop_front<S,2> : tiny<typename S::t1, none, none>
{};

template<class S>
struct tiny_pop_front<S,3> : tiny<typename S::t1, typename S::t2, none>
{};


template<class S, class T, int N, int Size> 
struct tiny_insert
{
	BOOST_STATIC_ASSERT(0);
};

template<class S, class T, int Size>
struct tiny_insert<S,T,0,Size> : tiny<T, typename S::t0, typename S::t1>
{};

template<class S, class T, int Size>
struct tiny_insert<S,T,1,Size> : tiny<typename S::t0, T, typename S::t1>
{};

template<class S, class T, int Size>
struct tiny_insert<S,T,2,Size> : tiny<typename S::t0, typename S::t1, T>
{};

template<class S, class T, int N>
struct tiny_insert<S,T,N,3>
{
	BOOST_STATIC_ASSERT(0);
};

namespace boost { namespace mpl {
	template<>
	struct push_back_impl<tiny_tag>
	{
		template <class S, class T>
		struct apply
		{
			typedef typename tiny_insert<
				S, T
				,tiny_size<S>::value
				,tiny_size<S>::value
			>::type type;
		};
	};
}}

namespace boost { namespace mpl {
	template<>
	struct push_front_impl<tiny_tag>
	{
		template <class S, class T1>
		struct apply
		{
			typedef typename tiny_push_front<
				S, T1, tiny_size<S>::value >::type type;		
		};
	};
}}

namespace boost { namespace mpl {
	template<>
	struct insert_impl<tiny_tag>
	{
		template <class S, class It, class T>
		struct apply
		{
			typedef typename tiny_insert<
				S, T, It::value::value, 
				tiny_size<S>::value
			>::type type;
		};
	};
}}


namespace boost { namespace mpl {
	template<>
	struct pop_front_impl<tiny_tag>
	{
		template <class S>
		struct apply
		{
			typedef typename tiny_pop_front< S, tiny_size<S>::value >::type type;
		};
	};
}}


// front(S)
// end(S)
//
// begin( S )
// end( S )
// pop_front(S,T)
// clear(S)



struct test0 : tiny<int, float, long> {};
struct test : tiny<double, float, char> {};

struct test2
{
	typedef mpl::at<test, 
		tiny_iterator< test, mpl::int_<1> > >::type type;
};

struct test3
{
	typedef mpl::advance< 
		tiny_iterator< test, mpl::int_<0> >,
		mpl::int_<2> >::type type;
};

struct test4
{
	typedef mpl::at<test, 
		tiny_iterator< test, mpl::int_<2> > >::type type;
};

template<class T=int>
struct wrapAssert : T
{
	typedef typename T type;
	BOOST_STATIC_ASSERT(0);
};

struct test5 :
	mpl::eval_if< 
	boost::is_same< 
	typename test2::type
	, float
	>
	, none
	, wrapAssert<>
	>
{};

struct test6 :
	mpl::eval_if< 
	boost::is_same< typename test3::type, char >
	, none
	, wrapAssert<>
	>
{};

struct test7:
	mpl::eval_if< 
	boost::is_same< typename test4::type, char>
	, none
	, wrapAssert<>
	>
{};

struct test8:
	mpl::eval_if< 
	boost::is_same< 
	typename mpl::deref< typename mpl::begin< test >::type >::type
	, double
	>
	, none
	, wrapAssert<>
	>
{};

struct test9:
	mpl::eval_if< 
	mpl::equal< tiny_size< tiny<int,int> >
	, mpl::int_<2> >
	, none
	,wrapAssert<>
	>
{};


struct test10 :
	mpl::eval_if< 
	mpl::equal< tiny_size< typename mpl::clear< test >::type >
	, mpl::int_<0> >
	, none
	, wrapAssert<>
	>
{};

struct test11:
		mpl::push_back< tiny<int,char>, double >::type
{};

struct test12:
	mpl::push_front< tiny<int,char>, double >::type
{};

struct testTiny : tiny<int, float, none> {};
struct test13:
	mpl::insert< typename testTiny::type, 
		tiny_iterator<testTiny, mpl::int_<0> >, int>::type
{};


void main()
{
	std::cout << "aa" << std::endl;

	mpl::push_back< tiny<int,float>, double >::type;
	mpl::push_front< tiny<int,float>, double >::type;
//	mpl::deref< mpl::begin< tiny<int> >::type >::type bb;

	// 	int a = tiny_size< test0::type >::value;
	// 	test4::type b;

	int c= mpl::int_<1>::value;

//	mpl::seq


}
