// ex2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
// 2012-12-08


#include "stdafx.h"

template<class X, class UnaryOp1, class UnaryOp2>
X apply_fg( X x, UnaryOp1 f, UnaryOp2 g)
{
	return f(g(x));
}

int func1( int x )
{
	return x+10;
}
int func2( int x )
{
	return x+10;
}


#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>

namespace std {

	template <bool use_swap> struct iter_swap_impl;

	template <class ForwardIterator1, class ForwardIterator2>
	void iter_swap( ForwardIterator1 i1, ForwardIterator2 i2)
	{
		typedef iterator_traits<ForwardIterator1> traits1;
		typedef typename traits1::value_type v1;
		typedef typename traits1::reference r1;

		typedef iterator_traits<ForwardIterator2> traits2;
		typedef typename traits2::value_type v2;
		typedef typename traits2::reference r2;

		bool const use_swap = boost::is_same<v1,v2>::value 
			&& boost::is_reference<r1>::value
			&& boost::is_reference<r2>::value;

		iter_swap_impl<use_swap>::do_it(i1, i2);
	}

	template<>
	struct iter_swap_impl<true>
	{
		template <class ForwardIterator1, class ForwardIterator2>
		static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
		{
			std::swap(*i1, *i2);
		}
	};

	template<>
	struct iter_swap_impl<false>
	{
		template <class ForwardIterator1, class ForwardIterator2>
		static void do_it(ForwardIterator1 i1, ForwardIterator2 i2)
		{
			typename iterator_traits<ForwardIterator1>::value_type tmp = *i1;
			*i1 = *i2;
			*i2 = tmp;
		}
	};

};

struct s
{
	int a[10];
	char b[ 31];
};


namespace prac
{
	template<class T, bool is_ref> struct const_ref;

	template <class T>
	struct add_const_ref
	{
		static const bool is_ref = boost::is_reference<T>::value;
		typedef typename const_ref<T, is_ref>::type type;
	};

	template<class T>
	struct const_ref<T, true>
	{
		typedef typename boost::remove_reference<T>::type type;
 	};

	template<class T>
	struct const_ref<T, false>
	{
		typedef typename T const& type;
	};
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a = apply_fg( 1, func1, func2 );
	printf ( "a=%d\n", a);

	std::list<std::string> strList;
	std::vector<std::string> strVector;

	strList.push_back( "a" );
	strList.push_back( "b" );

	strVector.push_back( "c" );
	strVector.push_back( "d" );

	std::list<std::string>::iterator it1 = strList.begin();
	std::vector<std::string>::iterator it2 = strVector.begin();
	std::iter_swap(it1, it2);

// 	int a = 0;
// 	boost::is_float<a>::value;

	int aaa =boost::alignment_of<s>::value;
	
//	const int bbb = 100;
//	bbb =11;

	bool r0 = boost::is_reference<float&>::value;
	bool r01 = boost::is_same<float,float>::value;
	bool r02 = boost::is_same<float, prac::add_const_ref<float&>::type>::value;
	bool r03 = boost::is_same<bool, prac::add_const_ref<float&>::type>::value;
	bool r04 = boost::is_same<float, prac::add_const_ref<float&>::type>::value;
	bool r05 = boost::is_same<const float, prac::add_const_ref<float>::type>::value;
	bool r06 = boost::is_same<s, prac::add_const_ref<float>::type>::value;
	bool r07 = boost::is_same<s, boost::remove_reference<s&>::type>::value;



	bool r1 = boost::is_same<s, prac::add_const_ref<s&>::type>::value;
	bool r2 = boost::is_same<const s&, prac::add_const_ref<s>::type>::value;

	return 0;
}

