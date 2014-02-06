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

struct sizeandType_tag{};
template<class Size, class Type>
struct sizeAndType
{
//	typedef typename Size::value tag;
	typedef typename Size type;
	typedef typename Type value;
};

struct size2Int
{
	template<class T1>
	struct apply
	{
		typedef typename 
			sizeAndType< mpl::integral_c<int, mpl::sizeof_<T1>::value >
			, T1> type;
	};
};


struct compare1
{
	template<class T1, class T2>
	struct apply
	{
		typedef typename T1 type;
		typedef typename T1 value;
	};
};


template<class S>
struct smallest
{
	typedef typename 
		mpl::deref<
			typename mpl::min_element<
				typename mpl::copy<S>::type
				//typename mpl::transform<S,size2Int>::type
				,mpl::less<mpl::sizeof_<mpl::_1>, mpl::sizeof_<mpl::_1> >
				//, compare1

			>::type
		>::type type;
};


struct v :
	mpl::vector<double&, int[2], char[100], char, short, int[4], long[2], float[20]>
	//mpl::vector_c<int, 4,5,2,3,1,4,7,3,2>
{
};


struct test1 :
	mpl::eval_if<
		boost::is_same<
			short
			,typename smallest<v>::type
		>
		,none
		//,wrapAssert<>
		,none
	>
{};


//typedef mpl::int_< mpl::sizeof_<_>::value > toSize;


typedef mpl::sizeof_<_> toSize;
typedef mpl::plus<_, mpl::int_<5> > add5;
typedef mpl::vector_c<int,1,2,3> v123;
typedef mpl::transform<v123, toSize>::type v678;

struct test2 :
	mpl::eval_if<
		mpl::equal<v678
		, mpl::vector_c<int,4,4,4> >
		,none
		//,wrapAssert<>
		,none
	>
{
};

//BOOST_STATIC_ASSERT(  );


void main()
{

	typedef std::list<int> IntList;
	IntList iList;
	iList.push_back(0);
	iList.push_back(1);
	iList.push_back(2);
	iList.push_back(3);
	int x;
	//std::for_each(iList.begin(), iList.end(), bind(&x, mpl::_1) );

 	smallest<v>::type a;
	mpl::transform<v,size2Int>::type b;

// 	mpl::min_element<
// 
// 		//typename mpl::copy<v>::type
// 		typename mpl::transform<v, add5>::type
// 
// 		,//mpl::less<mpl::sizeof_<_>, mpl::sizeof_<_> >
// 		mpl::less<_,_>
// 	>::type b;
// 
	v123 aa;
	v678 cc;
	int n0 = mpl::sizeof_<int>::value;
	int n1 = mpl::sizeof_<int[2]>::value;
	int n2 = mpl::sizeof_<char>::value;
	int n3 = mpl::sizeof_<double&>::value;




}
