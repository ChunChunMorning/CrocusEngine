# include "../Transform.hpp"
# include "../Entity.hpp"

using namespace s3d;

namespace cre
{
	Vec3 Transform::setPosition(const Vec3& position)
	{
		return m_position = entity()->parent() == nullptr ?
			position :
			(position - entity()->parent()->transform().lock()->position());
	}

	Vec3 Transform::position() const
	{
		return entity()->parent() == nullptr ?
			m_position :
			(entity()->parent()->transform().lock()->position() + m_position);
	}
}
