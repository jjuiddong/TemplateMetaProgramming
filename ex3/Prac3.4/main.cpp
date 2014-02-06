// practice 3.4

#include <iostream>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/type_traits/is_float.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/apply.hpp>
using namespace boost::mpl::placeholders;
#include <iterator>
#include <utility>
#include <list>
#include <vector>
#include <string>
#include <assert.h>

namespace mpl = boost::mpl;

typedef mpl::vector_c<int, 1, 0, 0, 0> mass;
typedef mpl::vector_c<int, 0, 1, 0, 0> length;
typedef mpl::vector_c<int, 0, 0, 1, 0> time;
typedef mpl::vector_c<int, 0, 1, -2, 0> accel;
typedef mpl::vector_c<int, 1, 1, -2, 0> force;
typedef mpl::vector_c<int, 0, 0, 0, 0> scalar;


template <class T, class Dimension>
struct Quantity
{
	Quantity(T x) : m_value(x) {}
	template <class OtherDimension>
	Quantity( Quantity<T, OtherDimension> &rhs) : m_value(rhs.value()) 
	{
		BOOST_STATIC_ASSERT((
			mpl::equal< Dimension, OtherDimension >::type::value
			));	
	}

	T m_value;
	T value() const { return m_value; }

	template<class OtherDimension>
	Quantity<T, Dimension>& operator=(Quantity<T, OtherDimension> &rhs)
	{
		BOOST_STATIC_ASSERT((
			mpl::equal< Dimension, OtherDimension >::type::value
			));

		if (this != &rhs)
		{
			m_value = rhs.value();
		}
		return *this;
	}

	Quantity<T, Dimension> operator+(const Quantity<T, Dimension> &rhs)
	{
		return Quantity<T, Dimension>(value() + rhs.value());
	}
	Quantity<T, Dimension> operator-(const Quantity<T, Dimension> &rhs)
	{
		return Quantity<T, Dimension>(value() - rhs.value());
	}

	struct minus_f
	{
		template <class T1, class T2>
		struct apply : mpl::minus<T1,T2> {};
	};

	template <class OtherDimension>
	Quantity<
		T, 
		typename mpl::transform<Dimension, OtherDimension, mpl::plus<_1,_2> >::type 
	> 
	operator*(const Quantity<T, OtherDimension> &rhs)
	{
		typedef typename mpl::transform<Dimension, OtherDimension, mpl::plus<_1,_2> >::type dim;
		return Quantity<T, dim>(value() * rhs.value());
	}

	template <class OtherDimension>
	Quantity<T, typename mpl::transform<Dimension, OtherDimension, minus_f>::type > 
		operator/(const Quantity<T, OtherDimension> &rhs)
	{
		typedef typename mpl::transform<Dimension, OtherDimension, minus_f>::type dim;
		return Quantity<T, dim>(value() / rhs.value());
	}

};

void main()
{
	Quantity<float, mass> m(3.f);
	Quantity<float, mass> m2(4.f);
	Quantity<float, length> l(5.f);
	Quantity<float, accel> a(5.f);
	Quantity<float, mass> m3 = m + m2;
	Quantity<float, mass> m4 = m - m2;
	Quantity<float, force> f = m * a;
	f = f+ m*a;

	m4 = f/a;



	BOOST_STATIC_ASSERT((
		mpl::plus<
		mpl::int_<2>
		,mpl::int_<3>
		,mpl::int_<4>
		>::type::value == 9
		));

}
