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
#include <boost/mpl/filter_view.hpp>

// #pragma warning(disable: 4819)
// #include <boost/spirit/core.hpp>
// #include <boost/spirit/attribute.hpp>



// using namespace boost::mpl::placeholders;
namespace mpl = boost::mpl;
// using namespace boost::lambda;


#include <iterator>
#include <utility>
#include <list>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <algorithm>

#include "fsm.h"



struct play{};
struct open_close{};
struct cd_detected
{
	cd_detected() {}
	cd_detected(std::string s1, std::string s2) : str1(s1), str2(s2) {}
	std::string str1;
	std::string str2;
};

struct pause{};
struct stop{};

class player : public state_machine<player>
{
private:
	enum states {Empty, Open, Stopped, Playing,
		Paused, initial_state = Empty };

	void start_playback(play const&)
	{
		int a = 0;

	}

	void open_drawer(open_close const&)
	{
int a = 0;
	}

	void close_drawer(open_close const&)
	{
int a = 0;
	}

	void store_cd_info(cd_detected const&e)
	{
int a = 0;
	}

	void stop_playback(stop const&)
	{
int a = 0;
	}

	void pause_playback(pause const&)
	{
int a = 0;
	}

	void resume_playback(play const&)
	{
int a = 0;
	}

	void stop_and_open(open_close const&)
	{
int a = 0;
	}


	friend class state_machine<player>;
	typedef player p;

	struct transition_table : mpl::vector<
		row< Stopped,	play,			Playing,	&p::start_playback >,
		row< Stopped,	open_close,		Open,		&p::open_drawer >,

		row< Open,		open_close,		Empty,		&p::close_drawer >,
		
		row< Empty,		open_close,		Open,		&p::open_drawer >,
		row< Empty,		cd_detected,	Stopped,	&p::store_cd_info >,

		row< Playing,	stop,			Stopped,	&p::stop_playback >,
		row< Playing,	pause,			Paused,		&p::pause_playback >,
		row< Playing,	open_close,		Open,		&p::stop_and_open >,

		row< Paused,	play,			Playing,	&p::resume_playback >,
		row< Paused,	stop,			Stopped,	&p::stop_playback >,
		row< Paused,	open_close,		Open,		&p::stop_and_open >
	> {};

};


void main()
{
	player p;

	p.process_event(open_close());
	p.process_event(open_close());
	p.process_event(cd_detected("aa", "bb"));
	p.process_event(play());


}
