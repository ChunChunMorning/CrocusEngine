# include "../Entity.hpp"
# include "../Component.hpp"
# include "../Transform.hpp"

using namespace s3d;

namespace cre
{
	Entity::Entity(const Vec3& position) :
		m_state(State::Uninitialized),
		m_parent(nullptr),
		m_transform(std::make_shared<Transform>(position))
	{
		m_transform->m_entity = this;
	};

	void Entity::init()
	{
		for (const auto& component : m_components)
		{
			component->init();
		}
	}

	void Entity::update()
	{
		if (m_state == State::Uninitialized)
		{
			m_state = State::Initialized;

			init();
		}

		Erase_if(m_children, [](const shared_ptr<Entity>& e) { return e->m_state == State::Removed; });

		for (const auto& child : m_children)
		{
			child->update();
		}
	}

	void Entity::remove()
	{
		m_state = State::Removed;
	}

	void Entity::addChild(shared_ptr<Entity>&& child, bool isAbsolute)
	{
		assert(child.unique());

		if (isAbsolute)
		{
			const auto position = child->m_transform->position();

			child->m_parent = this;
			child->m_transform->setPosition(position);
		}
		else
		{
			child->m_parent = this;
		}

		m_children.push_back(std::move(child));
	}

	void Entity::addComponent(shared_ptr<Component>&& component)
	{
		assert(component.unique());

		component->m_entity = this;
		m_components.push_back(std::move(component));
	}

	Array<weak_ptr<Entity>> Entity::children() const
	{
		Array<weak_ptr<Entity>> children;

		for (const auto& child : m_children)
		{
			if (child->m_state == State::Uninitialized)
			{
				continue;
			}

			children.push_back(child);
		}

		return children;
	}

	unique_ptr<Entity> Entity::Create(const Vec3& position)
	{
		return unique_ptr<Entity>(new Entity(position));
	}
}
