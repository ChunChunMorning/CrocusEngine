# pragma once
# include <Siv3D.hpp>
# include "Pointer.hpp"

namespace cre
{
	using namespace s3d;

	class Component;
	class Transform;

	class Entity
	{
	private:

		enum class State
		{
			Uninitialized, Initialized, Removed
		} m_state;

		stupid_ptr<Entity> m_parent;

		Array<shared_ptr<Entity>> m_children;

		shared_ptr<Transform> m_transform;

		std::vector<shared_ptr<Component>> m_components;

		Entity(const Vec3& position);
		Entity(const Entity&) = delete;
		Entity& operator =(const Entity&) = delete;

		void init();

	public:

		void update();

		void remove();

		void addChild(shared_ptr<Entity>&& child, bool isAbsolute = true);

		void addComponent(shared_ptr<Component>&& component);

		template<class T, class ... Args>
		void addComponent(Args&& ... args)
		{
			addComponent(std::make_shared<T>(std::forward<Args>(args)...));
		}

		stupid_ptr<Entity> parent() const
		{
			return m_parent;
		}

		Array<weak_ptr<Entity>> children() const;

		weak_ptr<Transform> transform() const
		{
			return m_transform;
		}

		template<class T>
		weak_ptr<T> getComponent() const
		{
			for (const auto& component : m_components)
			{
				const auto ptr = std::dynamic_pointer_cast<T>(component);

				if (ptr != nullptr)
				{
					return ptr;
				}
			}

			return{};
		}

		template<class T>
		std::vector<weak_ptr<T>> getComponents() const
		{
			std::vector<weak_ptr<T>> result;

			for (const auto& component : m_components)
			{
				const auto ptr = std::dynamic_pointer_cast<T>(component);

				if (ptr != nullptr)
				{
					result.push_back(ptr);
				}
			}

			return result;
		}

		template<class T>
		weak_ptr<T> findComponent(T* component) const
		{
			for (const auto& myComponent : m_components)
			{
				if (myComponent.get() == component)
				{
					return std::dynamic_pointer_cast<T>(myComponent);
				}
			}

			return{};
		}

		static unique_ptr<Entity> Create(const Vec3& position = Vec3::Zero);
	};
}
