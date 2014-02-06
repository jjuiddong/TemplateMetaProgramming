// metafunciton test

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


// 메타함수 클래스
struct argStr_f
{
	// 메타함수
	template<class T1, class T2>
	struct argStr
	{
		T1 t1;
		T2 t2;
		typedef typename argStr<T1,T2> type;
	};
};

template<class T1, class T2, class T3>
struct makeStruct
{
//	T1<T2, T3> m1;
	typedef typename T1::argStr<T2,T3>::type type;

};


void main()
{
	makeStruct<argStr_f, char, int>::type info;
	info.t1 = 'a';
	info.t2 = 10;

}
