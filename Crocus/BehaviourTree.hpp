# pragma once
# include <Siv3D.hpp>
# include "Entity.hpp"
# include "Pointer.hpp"

namespace cre
{
	namespace Behaviour
	{
		class Node
		{
		public:

			virtual ~Node() = default;

			virtual void setEntity(const stupid_ptr<Entity>& entity) = 0;

			virtual void init() {};

			virtual void entry() {};

			virtual Optional<bool> update() = 0;

			virtual void exit() {};
		};

		class Action : public Node
		{
		private:

			stupid_ptr<Entity> m_entity;

		protected:

			void setEntity(const stupid_ptr<Entity>& entity)
			{
				m_entity = entity;
			}

			stupid_ptr<Entity> entity() const
			{
				assert(m_entity != nullptr);

				return m_entity;
			}

		public:

			virtual ~Action() = default;
		};

		class Not : public Node
		{
		private:

			unique_ptr<Node> m_child;

			Optional<bool> m_current;

		public:

			Not(unique_ptr<Node>&& child) : m_child(std::move(child)) {}

			void setEntity(const stupid_ptr<Entity>& entity) override
			{
				m_child->setEntity(entity);
			}

			void init() override
			{
				m_child->init();
			}

			void entry() override
			{
				m_child->entry();
			}

			Optional<bool> update() override
			{
				m_current = m_child->update();

				return m_current ? !m_current.value() : m_current;
			}

			void exit() override
			{
				m_child->exit();
			};
		};

		template<bool allOf>
		class Logic : public Node
		{
		private:

			Array<unique_ptr<Node>> m_children;

			Optional<size_t> m_isRunning;

			void addChild(unique_ptr<Node>&& node)
			{
				m_children.push_back(std::move(node));
			}

			void addChildren() {}

			template<class Head, class ... Tail>
			void addChildren(Head&& head, Tail&& ... tail)
			{
				addChild(std::forward<Head>(head));
				addChildren(std::forward<Tail>(tail)...);
			}

		public:

			template<class ... Node>
			Logic(Node&& ... children)
			{
				addChildren(std::forward<Node>(children)...);
			}

			void setEntity(const stupid_ptr<Entity>& entity) override
			{
				for (auto& child : m_children)
				{
					child->setEntity(entity);
				}
			}

			void init() override
			{
				for (auto& child : m_children)
				{
					child->init();
				}
			}

			void init(const stupid_ptr<Entity>& entity)
			{
				setEntity(entity);

				init();
			}

			Optional<bool> update() override
			{
				for (auto i = m_isRunning.value_or(0); i < m_children.size(); ++i)
				{
					if (!m_isRunning)
					{
						m_children[i]->entry();
					}

					const auto status = m_children[i]->update();

					if (!status)
					{
						m_isRunning = i;
						return none;
					}

					m_isRunning = none;
					m_children[i]->exit();

					if (status.value() != allOf)
					{
						return !allOf;
					}
				}

				return allOf;
			}

			void exit() override
			{
				if (m_isRunning)
				{
					m_children[m_isRunning.value()]->exit();
				}
			}
		};

		using Sequence = Logic<true>;
		using Selector = Logic<false>;
	}
}
