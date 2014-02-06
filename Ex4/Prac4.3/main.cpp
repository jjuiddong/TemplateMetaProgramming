// Practice 4.3

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
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/multiplies.hpp>
using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;


struct test
{
	template<class N>
	struct apply
	{
		typedef typename mpl::equal_to< N, mpl::int_<2> >::type type;
	};
};

// 1
template <typename N, typename Predicate >
struct next_if :
	mpl::eval_if<
	typename mpl::apply<Predicate,N>::type
	,mpl::next<N>
	,N>
{ };


// 2
template <typename N1, typename N2>
struct formula :
	mpl::eval_if<
		mpl::not_equal_to<N1, N2>
		, mpl::eval_if<
			mpl::greater<N1,N2>
			, mpl::minus<N1,N2>
			, N1
			>
		, mpl::plus< N1, mpl::multiplies<N1, mpl::int_<2> > >
	>
{ };


void main()
{
	std::cout << "aa" << std::endl;


	// 1
	bool r1 = mpl::equal_to<
		typename next_if< mpl::int_<2>, test >::type
		, mpl::int_<3>
	>::value;


	// 2
	bool r2 = mpl::equal_to<
		typename formula< mpl::int_<3>, mpl::int_<2> >
		, mpl::int_<1>
	>::value;

}
