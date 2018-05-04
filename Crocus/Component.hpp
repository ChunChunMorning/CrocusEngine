# pragma once
# include "Pointer.hpp"

namespace cre
{
	class Entity;

	class Component
	{
		friend Entity;

	private:

		stupid_ptr<Entity> m_entity;

		Component(const Component&) = delete;
		Component& operator =(const Component&) = delete;

	public:

		Component() = default;

		virtual ~Component() = default;

		virtual void init() {};

		stupid_ptr<Entity> entity() const noexcept
		{
			return m_entity;
		}
	};
}
