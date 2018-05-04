# include "RigidbodyManager.hpp"
# include "../BoxCollider.hpp"
# include "../Coordinate.hpp"
# include "../Engine.hpp"
# include "../Rigidbody.hpp"
# include "ColliderManager.hpp"

using namespace s3d;

namespace cre
{
	void RigidbodyManager::update()
	{
		for (auto& rigidbodies : m_rigidbodies)
		{
			Erase_if(
				rigidbodies.second,
				[](const weak_ptr<Rigidbody>& e) { return e.expired(); }
			);
		}

		if (!m_intervaler.check())
		{
			return;
		}

		for (const auto& rigidbodies : m_rigidbodies)
		{
			for (const auto& rigidbody : rigidbodies.second)
			{
				const auto rigid = rigidbody.lock();

				if (!rigid->collider()->isActive())
				{
					rigid->setVelocity(Vec3::Zero);

					continue;
				}

				if (rigid->gravity())
				{
					rigid->addVelocity(Physics::Gravity * m_intervaler.interval());
				}

				rigid->setVelocity(Clamp(1 - 0.027 * rigid->drag(), 0.0, 1.0) * rigid->velocity());
				rigid->collider()->moveBy(rigid->velocity() * m_intervaler.interval());
			}
		}
	}

	void RigidbodyManager::escape()
	{
		for (const auto& rigidbodies : m_rigidbodies)
		{
			for (const auto& rigidbody : rigidbodies.second)
			{
				const auto rigid = rigidbody.lock();

				if (!rigid->collider()->isActive())
				{
					rigid->m_previousCenter = rigid->collider()->center();

					continue;
				}

				Engine::GetCollider()->escape(rigid);
				rigid->m_previousCenter = rigid->collider()->center();
			}
		}
	}

	void RigidbodyManager::Add(const weak_ptr<Rigidbody>& rigidbody)
	{
		const auto group = rigidbody.lock()->collider()->group();

		Engine::GetRigidbody()->m_rigidbodies[group].push_back(rigidbody);
	}

# ifdef _DEBUG
	void RigidbodyManager::draw() const
	{
		for (const auto& rigidboies : m_rigidbodies)
		{
			for (const auto& rigidbody : rigidboies.second)
			{
				const auto rigid = rigidbody.lock();

				rigid->collider()->draw(
					1 / Coordinate::PixelsPerUnit,
					rigid->collider()->isActive() ? Palette::Orange : Palette::Darkorange
				);
			}
		}
	}
# endif
}
