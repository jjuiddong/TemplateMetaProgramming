// practice 3.0

#include <iostream>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
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


// 메타함수를 인스턴스화 할 때 오류를 검사하는 방식으로 했다.
// 다른 방법은 찾지 못했음. ㅜㅜ;;
template <unsigned long N>
struct binary
{
	static unsigned const value = 
		binary<N/10>::value * 2 + N%10;

	int m_value;
	int Value() const { return m_value; }
	binary() : m_value(value)
	{
		BOOST_STATIC_ASSERT( N%10 == 0 || N%10 == 1 );
	}
};


template <>
struct binary<0>
{
	static unsigned const value = 0;
};


void main()
{
//	printf( "%d\n", binary<1101>::value );

	binary<1101> a;
	printf( "%d\n", a.Value() );

}
