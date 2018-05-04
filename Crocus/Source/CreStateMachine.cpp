# include "../StateMachine.hpp"

namespace cre
{
	stupid_ptr<Entity> StateBase::entity() const
	{
		return m_stateMachine->entity();
	}

	void StateBase::transition(const String& key)
	{
		m_stateMachine->transition(key);
	}

	void StateBase::set(stupid_ptr<StateMachine> stateMachine)
	{
		m_stateMachine = stateMachine;
	}

	StateMachine::StateMachine() :
		m_state(std::make_unique<StateBase>()) {}

	void StateMachine::reset()
	{
		m_state.reset();
		m_state = std::make_unique<StateBase>();
		m_next.clear();
	}

	void StateMachine::update()
	{
		if (!m_next.isEmpty)
		{
			m_state->exit();
			m_state = m_fuctories[m_next]();
			m_next.clear();
			m_state->entry();
		}

		m_state->update();
	}

	void StateMachine::exit()
	{
		m_state->exit();
	}

	void StateMachine::transition(const String& key)
	{
		assert(m_fuctories.find(key) != m_fuctories.end());

		m_next = key;
	}
}
