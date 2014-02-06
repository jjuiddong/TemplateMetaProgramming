// chapter 11


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
#include <boost/mpl/print.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>


// using namespace boost::mpl::placeholders;
//namespace mpl = boost::mpl;
// using namespace boost::lambda;

#include <iterator>
#include <utility>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

using namespace boost;
//using namespace boost::mpl;

struct x
{
	float foo(float f) const { return f+1.0f; }
} obj;

bool less_int(int x, int y)
{
	return x < y;
}

void main()
{
	float f = bind(&x::foo, _1, _2)(obj, 10.f);

// 	int v[5] = {10,0,1,2,4};
// 	int N = 2;
// 	int *i = std::find_if( v, v+5, bind(&less_int, _1, N) );
// 	printf( "%d\n", *i);
// 
// 	bool r = bind(&less_int, _1, N)( 1 );

	float a[5] = {1,2,3,4,5};
	BOOST_FOREACH(float k, a)
	{
		std::cout << k << std::endl;
	}

	typedef struct data
	{
		int a;
		int b;
		data() {}
		data(int _a, int _b) : a(_a), b(_b) {}
	}Data;

	typedef std::list<Data> DataList;
	typedef DataList::iterator DataItor;
	DataList lst;
	lst.push_back(Data(10,11));
	lst.push_back(Data(11,11));
	lst.push_back(Data(12,11));
	lst.push_back(Data(13,11));
	lst.push_back(Data(14,11));
	BOOST_FOREACH(const Data &d, lst)
	{
		std::cout << d.a << std::endl;
	}

}
