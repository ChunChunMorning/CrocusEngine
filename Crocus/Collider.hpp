# pragma once
# include <Siv3D.hpp>
# include "Component.hpp"
# include "Physics.hpp"

namespace cre
{
	using namespace s3d;

	class Rigidbody;

	class Collider : public Component
	{
	private:

		bool m_isActive;

		Physics::Group m_group;

	public:

		explicit Collider(Physics::Group group = Physics::Groups::Environment) :
			m_isActive(true), m_group(group)
		{
			assert(!m_group.isComplex());
		}

		void init() override;

		bool activate(bool isActive)
		{
			return m_isActive = isActive;
		}

		bool isActive() const { return m_isActive; }

		const Physics::Group& group() const { return m_group; }

		virtual Vec3 position() const = 0;

		Vec3 center() const
		{
			return position() + Vec3(0, size().y / 2, 0);
		}

		virtual Vec3 size() const = 0;

		virtual Vec3 groundNormal() const = 0;

		virtual bool intersects(const Box& other) const = 0;

		virtual bool intersects(const Ray& other) const = 0;

		virtual Optional<Vec3> intersectsAt(const Ray& other) const = 0;

		virtual bool detectWall(const Box& body, const Vec3& direction) const = 0;

		virtual void extrude(const stupid_ptr<Rigidbody>& rigidbody) const = 0;

# ifdef _DEBUG
		virtual void draw(double thickness, const Color& color) const = 0;
# endif
	};
}
