// Practice 4.4

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


// 1. is_data_member_pointer
template<class T>
struct is_data_member_pointer :
	boost::is_member_pointer<T>
{};

// 2. is_pointer_to_function
template<class T>
struct is_pointer_to_function:
	mpl::and_< 
		boost::is_function<T>
		,	boost::is_pointer<T>
	>
{};


// 3. is_reference_to_function_pointer
template<class T>
struct is_reference_to_function_pointer :
	mpl::and_<
	boost::is_function<T>
	, boost::is_reference<T>
	>
{};


// 4. is_reference_to_non_const
template<class T>
struct is_reference_to_non_const:
	mpl::and_<
	boost::is_reference<T>

	, typename mpl::not_< 
		typename boost::is_const<
		typename boost::remove_reference<T>::type // const T& 는 const로 인식하지 않으므로 reference를 제거하고 판단함
		>::type
	>

	
	>
{};


void main()
{
	std::cout << "aa" << std::endl;

//	typedef void(*)(void) func;
	typedef int (*Func)(char *);

	bool r1 = is_pointer_to_function<
		Func >::value;

	bool r2 = boost::is_reference<const int &>::type::value;

	bool r3 = is_reference_to_non_const<const int &>::value;
	bool r4 = is_reference_to_non_const<int &>::value;


}
