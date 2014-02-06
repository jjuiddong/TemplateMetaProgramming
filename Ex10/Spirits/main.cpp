// chapter 10


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

#pragma warning(disable: 4819)
#include <boost/spirit/core.hpp>
#include <boost/spirit/attribute.hpp>



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

//using namespace boost;
//using namespace boost::mpl;

using namespace boost::spirit;
using namespace phoenix;

struct vars : boost::spirit::closure<vars, int>
{
	member1 value;
};

struct calculator
	: public grammar<calculator, vars::context_t>
{
	template<class Tokenizer>
	struct definition
	{
		rule<Tokenizer, vars::context_t>
			expression, term, factor, group, integer;

		rule<Tokenizer> top;

		definition(calculator const &self)
		{
			top = expression[self.value = arg1];

			group = '(' >> expression[group.value = arg1] >> ')';

			factor = integer[factor.value = arg1] 
				| group[factor.value = arg1]
				;

			term = factor[term.value = arg1]
			>> *( ('*' >> factor[term.value *= arg1])
				| ('/' >> factor[term.value /= arg1])
				)
				;

			expression = term[expression.value = arg1]
			>> *( ('+' >> term[expression.value += arg1])
				| ('-' >> term[expression.value -= arg1])
				)
				;

			integer = int_p[integer.value = arg1];
		}

		rule<Tokenizer> const &start() { return top; }

	};
};


void main()
{
	calculator calc;

	std::string str;
	while (std::getline(std::cin, str))
	{
		int n= 0;
// 		parse(str.c_str(), calc[var(n) = arg1], space_p);
// 		std::cout << "result = " << n << std::endl;

	}

}
