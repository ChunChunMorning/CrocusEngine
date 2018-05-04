# pragma once
# include <Siv3D.hpp>
# include "Assets.hpp"
# include "Component.hpp"
# include "Physics.hpp"

namespace cre
{
	using namespace s3d;

	class BoxCollider;

	class Rigidbody : public Component
	{
		friend class RigidbodyManager;

	private:

		Vec3 m_previousCenter;

		Vec3 m_velocity;

		Physics::Group m_mask;

		double m_drag;

		bool m_gravity;

		stupid_ptr<BoxCollider> m_collider;

	public:

		Rigidbody() = default;

		explicit Rigidbody(Physics::Group mask, double drag = 1.0, bool gravity = true);

		void init() override;

		Vec3 setVelocity(const Vec3& velocity) { return m_velocity = velocity; }

		Physics::Group setMask(Physics::Group mask) { return m_mask = mask; }

		double setDrag(double drag) { return m_drag = drag; }

		bool setGravity(bool gravity) { return m_gravity = gravity; }

		void teleport(const Vec3& position);

		Vec3 addVelocity(const Vec3& velocity)
		{
			return m_velocity += velocity;
		}

		const Vec3& previousCenter() const { return m_previousCenter; }

		const Vec3& velocity() const { return m_velocity; }

		const Physics::Group& mask() const { return m_mask; }

		double drag() const { return m_drag; }

		bool gravity() const { return m_gravity; }

		const stupid_ptr<BoxCollider>& collider() const { return m_collider; }

		static unique_ptr<Component> Create(const XMLElement& element, const Assets&);
	};
}
