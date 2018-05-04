# pragma once
# include <Siv3D.hpp>
# include "Component.hpp"
# include "Pointer.hpp"

namespace cre
{
	using namespace s3d;

	class Transform : public Component
	{
	private:

		Vec3 m_position;

	public:

		Transform(const Vec3& position = Vec3::Zero) : m_position(position) {}

		Vec3 setPosition(const Vec3& position);

		Vec3 setLocalPosition(const Vec3& localPosition)
		{
			return m_position = localPosition;
		}

		Vec3 moveBy(const Vec3& v)
		{
			return m_position.moveBy(v);
		}

		Vec3 position() const;

		const Vec3& localPosition() const
		{
			return m_position;
		}
	};
}
