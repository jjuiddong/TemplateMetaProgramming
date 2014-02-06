
// C++ template metaprogramming 책에 11장에 나오는 FSM 클래스다.

#pragma once



template<class Transition, class Next>
struct event_dispatcher
{
	typedef typename Transition::fsm_t fsm_t;
	typedef typename Transition::event event;

	static int dispatch(fsm_t &fsm, int state, event const &e)
	{
		if (state == Transition::current_state)
		{
			Transition::execute(fsm, e);
			return Transition::next_state;
		}
		else
		{
			return Next::dispatch(fsm, state, e);
		}
	}
};


template<class Derived>
class state_machine
{
protected:
	state_machine() : state(Derived::initial_state) {}
	int state;

	template<int CurrentState
		, class Event
		, int NextState
		, void (Derived::*action)(Event const &)
	>
	struct row
	{
		static int const current_state = CurrentState;
		static int const next_state = NextState;
		typedef Event event;
		typedef Derived fsm_t;

		static void execute(Derived& fsm, Event const &e)
		{
			(fsm.*action)(e);
		}
	};

public:
	template<class Event>
	int call_no_transition(int state, Event const &e)
	{
		return static_cast<Derived*>(this)->no_transition(e);
	}

	template<class Event>
	int no_transition(Event const& e)
	{
		assert(false);
		return state;
	}

	template<class Event>
	int process_event(Event const& evt)
	{
		typedef typename generate_dispatcher<
			typename Derived::transition_table, Event
		>::type dispatcher;

		this->state = dispatcher::dispatch(
			*static_cast<Derived*>(this)
			, this->state
			, evt
			);
		return this->state;
	}

};



template<class Transition>
struct transition_event
{
	typedef typename Transition::event type;
};

struct default_event_dispatcher
{
	template<class FSM, class Event>
	static int dispatch( state_machine<FSM> &m, int state, Event const &e)
	{
		return m.call_no_transition(state,e);
	}
};

template<class Table, class Event>
struct generate_dispatcher
	: mpl::fold<
		mpl::filter_view<
			Table
			, boost::is_same<Event, transition_event<mpl::_1> >
			>
		, default_event_dispatcher
		, event_dispatcher<mpl::_2, mpl::_1>
	>
{};
