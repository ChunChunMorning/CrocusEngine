# pragma once
# include "Assets.hpp"
# include "Collider.hpp"
# include "Transform.hpp"

namespace cre
{
	using namespace s3d;

	class BoxCollider : public Collider
	{
	private:

		Vec3 m_offset;

		Vec3 m_size;

		stupid_ptr<Transform> m_transform;

	public:

		BoxCollider() = default;

		explicit BoxCollider(const Vec3& size, Physics::Group group = Physics:: Groups::Environment);

		BoxCollider(const Vec3& offset, const Vec3& size, Physics::Group group = Physics::Groups::Environment);

		void init() override;

		Vec3 setOffset(const Vec3& offset) { return m_offset = offset; }

		Vec3 setPosition(const Vec3& position);

		Vec3 setCenter(const Vec3& center);

		Vec3 moveBy(const Vec3& v)
		{
			return m_transform->moveBy(v);
		}

		Vec3 offset() const { return m_offset; }

		Vec3 position() const override;

		Box box() const { return{ center(), m_size }; }

		Vec3 size() const override { return m_size; }

		Vec3 groundNormal() const override { return Vec3::Up; }

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
