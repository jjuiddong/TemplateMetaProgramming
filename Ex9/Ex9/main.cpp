//chapter 9


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


using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;
using namespace boost::lambda;

#include <iterator>
#include <utility>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

struct none {};
template<class T>
struct wrapAssert
{
	BOOST_STATIC_ASSERT(0);
};
template<class T>
struct wrap {};

struct print_type
{
	template<class T>
	void operator() (wrap<T>)
	{
		std::cout << typeid(T).name() << std::endl;
	};
};

typedef mpl::vector<int, double, int&, char*> v;


namespace crtp
{
	template<class T>
	struct signed_number
	{
		friend T abs(T x)
		{
			return x < 0? -x : x;
		}
	};
}

class Float : crtp::signed_number<Float>
{
public:
	Float(float x) : value(x) {}
	Float operator-() const { return Float(-value); }
	bool operator<(float x) const { return value < x; }
	float value;
};

void main()
{
	mpl::for_each<v, wrap<mpl::_1> >(print_type());

	const Float pi = -3.1415f;
	const Float pi2 = abs(pi);
//	crtp::signed_number<Float>::abs(Float(10));

}
