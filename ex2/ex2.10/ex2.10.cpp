// ex2.10.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
// practice 2-2
//

#include "stdafx.h"

#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>


template <class Target>
struct polymorphic_downcast
{
	template<bool is_ptr> struct do_cast;

	template <class Source>
	static Target cast(Source &x) // ���ڸ� ���۷����� ���־�� �߰��� �ӽ� ������ ĳ���� �Ǵ°� ���� �� �ִ�.
	{
		static const bool is_ptr = boost::is_pointer<Target>::value;
		return do_cast<is_ptr>::cast(x);
	}

	template<>
	struct do_cast<false>
	{
		template<class Source>
		static Target cast(Source &x)
		{
			assert( &dynamic_cast<Target>(x) == &x);
			return static_cast<Target>(x);
		}
	};

	template<>
	struct do_cast<true>
	{
		template<class Source>
		static Target cast(Source &x)
		{
			assert( dynamic_cast<Target>(x) == x);
			return static_cast<Target>(x);
		}
	};
};

struct A { virtual ~A() {} };
struct B : A {};

int _tmain(int argc, _TCHAR* argv[])
{
	B b;
	A *a_ptr = &b;
//	B *b_ptr = polymorphic_downcast::cast<B*>(a_ptr);
	
	B &c = b;
// 	B &bb = polymorphic_downcast<B&>::cast(c);
// 	B *b_ptr = polymorphic_downcast<B*>::cast(a_ptr);


//	B &c = static_cast<B&>(b);

//	B &d = static_cast<B&>(b);

	B &d = polymorphic_downcast<B&>::cast(b);
	B *b_ptr = polymorphic_downcast<B*>::cast(a_ptr);


	return 0;
}
