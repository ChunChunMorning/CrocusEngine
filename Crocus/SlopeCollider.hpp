# pragma once
# include "Assets.hpp"
# include "Collider.hpp"
# include "Transform.hpp"

namespace cre
{
	using namespace s3d;

	class SlopeCollider : public Collider
	{
	private:

		Vec3 m_offset;

		Vec3 m_size;

		Vec3 m_direction;

		stupid_ptr<Transform> m_transform;

	public:

		SlopeCollider() = default;

		SlopeCollider(const Vec3& size, const Vec3& direction, Physics::Group group = Physics::Groups::Environment);

		SlopeCollider(const Vec3& offset, const Vec3& size, const Vec3& direction, Physics::Group group = Physics::Groups::Environment);

		void init() override;

		Vec3 position() const override;

		Vec3 size() const override { return m_size; }

		Vec3 groundNormal() const override;

		bool intersects(const Box& other) const override;

		bool intersects(const Ray& other) const override;

		Optional<Vec3> intersectsAt(const Ray& other) const override;

		bool detectWall(const Box& body, const Vec3& direction) const override;

		void extrude(const stupid_ptr<Rigidbody>& rigidbody) const override;

# ifdef _DEBUG
		void draw(double thickness, const Color& color) const override;
# endif

		static unique_ptr<Component> Create(const XMLElement& element, const Assets&);
	};
}
