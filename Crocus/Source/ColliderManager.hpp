# pragma once
# include <map>
# include <Siv3D.hpp>
# include "../Physics.hpp"
# include "../Pointer.hpp"

namespace cre
{
	class Collider;
	class Rigidbody;

	class ColliderManager
	{
	private:

		std::map<Physics::Group, Array<weak_ptr<Collider>>> m_colliders;

	public:

		void erase();

		void escape(const stupid_ptr<Rigidbody>& rigidbody);

		template<class Primitive>
		weak_ptr<Collider> detect(const Primitive& primitive, Physics::Group mask) const
		{
			for (const auto& colliders : m_colliders)
			{
				if (!mask.contain(colliders.first))
				{
					continue;
				}

				for (const auto& collider : colliders.second)
				{
					const auto ptr = collider.lock();

					if (!ptr->isActive())
					{
						continue;
					}

					if (ptr->intersects(primitive))
					{
						return collider;
					}
				}
			}

			return{};
		}

		template<class Primitive>
		Array<weak_ptr<Collider>> detectAll(const Primitive& primitive, Physics::Group mask) const
		{
			Array<weak_ptr<Collider>> result;

			for (const auto& colliders : m_colliders)
			{
				if (!mask.contain(colliders.first))
				{
					continue;
				}

				for (const auto& collider : colliders.second)
				{
					const auto ptr = collider.lock();

					if (!ptr->isActive())
					{
						continue;
					}

					if (ptr->intersects(primitive))
					{
						result.push_back(collider);
					}
				}
			}

			return result;
		}

		std::pair<weak_ptr<Collider>, Vec3> detectAt(const Ray& ray, Physics::Group mask, double length) const;

		Array<std::pair<weak_ptr<Collider>, Vec3>> detectAtAll(const Ray& ray, Physics::Group mask, double length) const;

		bool detectWall(const Box& body, const Vec3& direction, Physics::Group mask) const;

		static void Add(const weak_ptr<Collider>& collider);

# ifdef _DEBUG
		void draw();
# endif
	};
}
