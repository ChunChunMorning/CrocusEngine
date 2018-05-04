# include "../Rigidbody.hpp"
# include "../BoxCollider.hpp"
# include "../Entity.hpp"
# include "../StringArgs.hpp"
# include "RigidbodyManager.hpp"

using namespace s3d;

namespace cre
{
	Rigidbody::Rigidbody(Physics::Group mask, double drag, bool gravity) :
		m_velocity(Vec3::Zero), m_mask(mask), m_drag(drag), m_gravity(gravity) {}

	void Rigidbody::init()
	{
		m_collider = entity()->getComponent<BoxCollider>();
		m_previousCenter = m_collider->center();

		RigidbodyManager::Add(entity()->findComponent(this));
	}

	void Rigidbody::teleport(const Vec3& position)
	{
		m_collider->setPosition(position);
		m_previousCenter = m_collider->center();
		m_velocity = Vec3::Zero;
	}

	unique_ptr<Component> Rigidbody::Create(const XMLElement& element, const Assets&)
	{
		const auto mask = GetArg<Physics::Group>(element, L"mask", Physics::Groups::Default);
		const auto drag = GetArg<double>(element, L"drag", 1.0);
		const auto gravity = GetArg<bool>(element, L"gravity", true);

		if (!mask || !drag || !gravity)
		{
			return nullptr;
		}

		return std::make_unique<Rigidbody>(mask.value(), drag.value(), gravity.value());
	}
}
