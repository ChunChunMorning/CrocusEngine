# pragma once
# include <unordered_map>
# include <Siv3D.hpp>
# include "Entity.hpp"
# include "Pointer.hpp"

namespace cre
{
	class StateMachine;

	class StateBase
	{
	private:

		stupid_ptr<StateMachine> m_stateMachine;

	protected:

		stupid_ptr<Entity> entity() const;

		void transition(const String& key);

	public:

		virtual ~StateBase() = default;

		void set(stupid_ptr<StateMachine> stateMachine);

		virtual void entry() {}

		virtual void update() {}

		virtual void exit() {}
	};

	class StateMachine
	{
	private:

		using Fuctory = std::function<unique_ptr<StateBase>()>;

		std::unordered_map<String, Fuctory> m_fuctories;

		String m_next;

		unique_ptr<StateBase> m_state;

		stupid_ptr<Entity> m_entity;

	public:

		StateMachine();

		void setEntity(const stupid_ptr<Entity>& entity)
		{
			m_entity = entity;
		}

		template<class State>
		void add(const String& key)
		{
			m_fuctories.emplace(
				key,
				[&]() {
				auto state = std::make_unique<State>();

				state->set(this);

				return state;
			}
			);

			if (m_next.isEmpty)
			{
				m_next = key;
			}
		}

		void reset();

		void update();

		void exit();

		void transition(const String& key);

		stupid_ptr<Entity> entity() const
		{
			assert(m_entity != nullptr);

			return m_entity;
		}
	};
}
