// practice 3.1

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
using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;


struct convert123to234
{
	typedef mpl::vector_c<int,1,2,3> seq;

	struct add_1
	{
		template <class T>
		struct apply// : boost::add_pointer< T >
		{
			//typedef  type;
			//static const int value = T+1;
			//typedef typename mpl::int_<0> type;
			//typedef typename boost::add_pointer<T>::type type;
			//typedef mpl::int_<0> type;
			typedef mpl::vector_c<int,2,3,4> type;
			//BOOST_STATIC_ASSERT( 0 );
		};

		template<>
		struct apply<int>
		{
//			BOOST_STATIC_ASSERT( 0 );
//			typedef mpl::int_<2>::type type;
			typedef float type;
		};

		template<>
		struct apply< mpl::int_<4> >
		{
			typedef mpl::int_<4>::type type;
		};
	};

	typedef mpl::transform< 
		seq, 
		add_1 > convert;
};


template <class T>
struct test
{
	T a;
	BOOST_STATIC_ASSERT( 0 );
};



void main()
{
	//mpl::transform
	bool b1 = mpl::equal<
		convert123to234::convert::type, 
		mpl::vector<int, mpl::int_<1>, mpl::int_<2>, mpl::int_<3>>
		//mpl::vector<int*,int*, float*, char*> 
		//mpl::vector<mpl::int_<0>,mpl::int_<0>,mpl::int_<0>,mpl::int_<0>> 
	>::value;
	
	bool b2 = mpl::equal<
			mpl::vector_c<int, 1,2,3>
			,	mpl::vector<int, mpl::int_<1>, mpl::int_<2>, mpl::int_<3> >
	>::value;

	bool b3 = mpl::equal<
				convert123to234::convert::type
			,	mpl::vector_c<int, 2,3,4>
	>::value;


	typedef mpl::transform<
		mpl::vector_c< int, 1, 2, 3 >::type,
		mpl::vector_c< int, 1, 1, 1 >::type,
		mpl::plus<_,_> >::type newType;

	bool b4 = mpl::equal<
			newType
		,	mpl::vector_c<int, 2,3,4>
	>::value;


}
