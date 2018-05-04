# include "ColliderManager.hpp"
# include "../Collider.hpp"
# include "../Coordinate.hpp"
# include "../Engine.hpp"
# include "../Rigidbody.hpp"

namespace cre
{
	void ColliderManager::erase()
	{
		for (auto& colliders : m_colliders)
		{
			Erase_if(
				colliders.second,
				[](const weak_ptr<Collider>& e) { return e.expired(); }
			);
		}
	}

	void ColliderManager::escape(const stupid_ptr<Rigidbody>& rigidbody)
	{
		for (const auto& colliders : m_colliders)
		{
			if (!rigidbody->mask().contain(colliders.first))
			{
				continue;
			}

			for (const auto& collider : colliders.second)
			{
				const auto ptr = collider.lock();

				if (rigidbody->entity() == ptr->entity() || !ptr->isActive())
				{
					continue;
				}

				ptr->extrude(rigidbody);
			}
		}
	}

	std::pair<weak_ptr<Collider>, Vec3> ColliderManager::detectAt(const Ray& ray, Physics::Group mask, double length) const
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

				const auto pos = ptr->intersectsAt(ray);

				if (pos && (pos.value() - ray.origin).length() < length)
				{
					return{ collider, pos.value() };
				}
			}
		}

		return{ weak_ptr<Collider>{}, Vec3{} };
	}

	Array<std::pair<weak_ptr<Collider>, Vec3>> ColliderManager::detectAtAll(const Ray& ray, Physics::Group mask, double length) const
	{
		Array<std::pair<weak_ptr<Collider>, Vec3>> result;

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

				const auto pos = ptr->intersectsAt(ray);

				if (pos && (pos.value() - ray.origin).length() < length)
				{
					result.emplace_back(collider, pos.value());
				}
			}
		}

		std::sort(
			result.begin(),
			result.end(),
			[&](const std::pair<weak_ptr<Collider>, Vec3>& lhs, const std::pair<weak_ptr<Collider>, Vec3>& rhs) {
				return ray.origin.distanceFromSq(lhs.second) < ray.origin.distanceFromSq(rhs.second);
			}
		);

		return result;
	}

	bool ColliderManager::detectWall(const Box& body, const Vec3& direction, Physics::Group mask) const
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

				if (ptr->detectWall(body, direction))
				{
					return true;
				}
			}
		}

		return false;
	}

# ifdef _DEBUG
	void ColliderManager::draw()
	{
		for (const auto& colliders : m_colliders)
		{
			for (const auto& collider : colliders.second)
			{
				const auto col = collider.lock();

				col->draw(
					1 / Coordinate::PixelsPerUnit,
					col->isActive() ? Palette::Green : Palette::Darkgreen
				);
			}
		}
	}
# endif

	void ColliderManager::Add(const weak_ptr<Collider>& collider)
	{
		Engine::GetCollider()->m_colliders[collider.lock()->group()].push_back(collider);
	}
}
