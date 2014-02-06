// chapter 6

#include <iostream>

/*
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
namespace mpl = boost::mpl;
/**/

#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>



void print(std::list<int> &lst)
{
	std::list<int>::iterator it = lst.begin();
	while (lst.end() != it)
		printf( "%d\n", *it++);
}

template<class T>
struct Print : std::unary_function<T,void>
{
	void operator() (const T &t)
	{
		std::cout << t << " " << std::endl;
	}
};

template<class T>
T Plus1(T &t)
{
	return t + 1;
};

void main()
{
	typedef std::list<int> IntList;
	IntList iList;
	IntList oList;
	iList.push_back(1);
	iList.push_back(2);
	iList.push_back(3);
	iList.push_back(4);

// 	oList.push_back(1);
// 	oList.push_back(2);
// 	oList.push_back(3);
// 	oList.push_back(4);

 	std::for_each( iList.begin(), iList.end(), Print<IntList::value_type>() );

	std::vector<int> v0;
	std::transform( iList.begin(), iList.end(), std::back_inserter(v0), Plus1<IntList::value_type> );
	std::for_each( v0.begin(), v0.end(), Print<int>() );

	typedef Print<IntList::value_type> PrintFunc;
	PrintFunc()( 10 );


	std::vector<int> v;
	std::copy(iList.begin(), iList.end(), std::back_inserter(v) );
	std::for_each( v.begin(), v.end(), Print<int>() );


	
	//print( intList );

}
