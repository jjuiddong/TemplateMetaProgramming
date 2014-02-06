// chapter5
// practice 5.0

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

namespace boost { namespace mpl {
	template<>
	struct push_front_impl<tiny_tag>
	{
		template <class S, class T1>
		struct apply :
			tiny<T1, typename S::t0, typename S::t1>
		{};
	};
}}


namespace boost { namespace mpl {
	template<>
	struct push_back_impl<tiny_tag>
	{
		template <class S, class T1>
		struct apply
		{
			template<class T1, class T2, class T3> struct push_back : tiny<T1,T2,T3> {};
			typedef typename push_back<typename S::t0, typename S::t1, typename S::t2>::type type;

			template<>
			struct push_back<none, none, none> : tiny<T1>
			{};

			template<class A1>
			struct push_back<A1, none, none> : tiny<A1,T1>
			{};

			template<class A1, class A2>
			struct push_back<A1, A2, none> : tiny<A1,A2,T1>
			{};
		};
	};
}}


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


// front(S)
// end(S)
//
// begin( S )
// end( S )
// push_front(S, T)
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


void main()
{
	std::cout << "aa" << std::endl;

	mpl::push_back< tiny<int,float>, double >::type;
	mpl::push_front< tiny<int,float>, double >::type;
	mpl::deref< mpl::begin< tiny<int> >::type >::type bb;

// 	int a = tiny_size< test0::type >::value;
// 	test4::type b;

	int c= mpl::int_<1>::value;


}
