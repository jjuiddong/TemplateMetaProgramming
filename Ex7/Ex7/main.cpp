// Chapter7,0

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


template <class IteratorSeq> // IteratorSeq: 순차열들의 순차열의 반복자
struct zip_iterator
{
	typedef mpl::forward_iterator_tag category;
	typedef typename IteratorSeq base;

	typedef typename mpl::transform<
		IteratorSeq
		,mpl::deref<mpl::_1>
	>::type type;
};

namespace boost{ namespace mpl {
	template<class IteratorSeq>
	struct next< zip_iterator<IteratorSeq> >
	{
		typedef zip_iterator<
			typename mpl::transform<
			IteratorSeq, mpl::next<mpl::_1> >::type > type;
	};
}}

template <class Sequences>
struct zip_view
	: mpl::iterator_range<
		zip_iterator<
		typename mpl::transform<
			Sequences, mpl::begin<mpl::_1>
		>::type 
	>
	,zip_iterator<
		typename mpl::transform<
			Sequences, mpl::end<mpl::_1>
		>::type
	>
	>		
{

};


void main()
{

}
