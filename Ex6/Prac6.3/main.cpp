// practice6.0

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
#include <boost/lambda/lambda.hpp>
#include <boost/mpl/max_element.hpp>
#include <boost/mpl/min_element.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/copy.hpp>

using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;
using namespace boost::lambda;

#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>


struct none{};
template<class T=int>
struct wrapAssert : T
{
	typedef typename T type;
	BOOST_STATIC_ASSERT(0);
};

struct v : mpl::vector_c<int,17,10,25,2,11>
{};

//typedef mpl::copy< v, binary_tree_inserter<tree<> > >:: type bst;
struct push_binary_tree
{
	template<class S, class T>
	struct apply
	{
		typedef typename mpl::push_back<S, mpl::integral_c<int,T::value> >::type  type;
	};
};

typedef mpl::copy< v, mpl::inserter<mpl::vector_c<int>, push_binary_tree > >:: type bst;


template<int Pos, int Level>
struct leftChild
{
	static const int value = Pos * 2 + 1;
};

template<int Pos, int Level>
struct rightChild
{
	static const int value = Pos * 2 + 2;
};

template<int Level>
struct downStair
{
	static const int value = Level+1;
};



template<class S, int Pos=0, int Level=0>
struct inorder_view
{
	template<bool traverse, class S, int Pos, int Level> struct trav{};

	static const bool traverse = mpl::less<mpl::int_<Pos>, mpl::size<S>::type>::type::value;
	typedef typename trav<traverse,S,Pos,Level>::type type;

	template<class S, int Pos, int Level>
	struct trav<true, S, Pos, Level>
	{
		typedef typename 
			mpl::copy< 
					typename inorder_view<S, rightChild<Pos,Level>::value, downStair<Level>::value>::type
				, 
				mpl::back_inserter<
					typename mpl::push_back< 
					typename inorder_view<S, leftChild<Pos,Level>::value, downStair<Level>::value>::type
					,  typename mpl::at<S, mpl::int_<Pos> >::type
					//mpl::int_<Pos>
					>::type
				>
			>::type		
			type;
	};

	template<class S, int Pos, int Level>
	struct trav<false, S, Pos, Level>
	{
		typedef typename mpl::vector_c<int> type;
	};

};


typedef mpl::copy< v, mpl::front_inserter<mpl::vector_c<int> > >:: type testV;

// struct test1 :
// 	mpl::eval_if<
// 		mpl::equal<
// 			mpl::vector_c<int,11,2,10,25,17>
// 			,testV
// 		>::type
// 		, none
// 		, wrapAssert<>
// 	>
// {};

// 
// struct test2 :
// 	mpl::eval_if<
// 		mpl::equal<mpl::vector_c<int,1,1,1,1,1>,bst>::type
// 	, none
// 	, wrapAssert<>
// 	>
// {};


struct test4 
	: inorder_view< bst >::type
{
};



// BOOST_STATIC_ASSERT(
// mpl::equal< inorder_view<bst>
// , mpl::vector_c<int,2,10,11,17,25>
// >::value ));

void main()
{
	bool b1 = mpl::greater<mpl::int_<1>, typename mpl::size<bst>::type>::type::value;
	inorder_view< bst >::type t2;

	typedef mpl::vector_c<int,1,2,3> v1;
	typedef mpl::copy< mpl::vector_c<int,4,5,6>,
		mpl::back_inserter< 
		 v1> >::type v2;

	v1 V1;
	v2 V2;

}

