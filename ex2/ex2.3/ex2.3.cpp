// practice 2.3
// practice 2.4
//

#include <iostream>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

using namespace  std;

char *typeNameStr[] = {
	"char",
	"short int",
	"int",
	"long",
};

template <class T>
struct type_descriptor
{
	template<class Type> struct typeName;

	template<>
	struct typeName<char>
	{
		static const int value = 0;
	};

	template<>
	struct typeName<int>
	{
		static const int value = 2;
	};

	template<>
	struct typeName<short int>
	{
		static const int value = 1;
	};

	template<>
	struct typeName<long int>
	{
		static const int value = 3;
	};

	static const int value = typeName<
		boost::remove_pointer< boost::remove_reference<T>::type >::type >::value;
	std::string name;

	operator char* ()
	{
		name = typeNameStr[ value];
		if (boost::is_reference<T>::value)
			name += "&";
		if (boost::is_pointer<T>::value)
			name += "*";
		return (char*)name.c_str();
	}
};

void func( char *(*[])() )
{
//	*f();

}

char* func2( )
{
	printf ("func2\n");
	return "aaa";
}


void main()
{
	cout << type_descriptor<short int*>() << endl;

	func( func2 );

}
