# include "../BoxCollider.hpp"
# include "../Entity.hpp"
# include "../Figure.hpp"
# include "../Physics.hpp"
# include "../Rigidbody.hpp"
# include "../StringArgs.hpp"

using namespace s3d;

namespace
{
	using namespace cre;

	Vec3 Escape(const Vec3& point, const Box& box)
	{
		double distance;
		Vec3 position;

		if (point.y > box.center.y)
		{
			distance = box.center.y + box.h / 2 - point.y;
			position = point + (distance + Physics::Margin) * Vec3::Up;
		}
		else
		{
			distance = point.y - (box.center.y - box.h / 2);
			position = point + (distance + Physics::Margin) * Vec3::Down;
		}

		if (point.x > box.center.x)
		{
			const auto d = box.center.x + box.w / 2 - point.x;

			if (d < distance)
			{
				distance = d;
				position = point + (distance + Physics::Margin) * Vec3::Right;
			}
		}
		else
		{
			const auto d = point.x - (box.center.x - box.w / 2);

			if (d < distance)
			{
				distance = d;
				position = point + (distance + Physics::Margin) * Vec3::Left;
			}
		}

		if (point.z > box.center.z)
		{
			const auto d = box.center.z + box.d / 2 - point.z;

			if (d < distance)
			{
				distance = d;
				position = point + (distance + Physics::Margin) * Vec3::Forward;
			}
		}
		else
		{
			const auto d = point.z - (box.center.z - box.d / 2);

			if (d < distance)
			{
				distance = d;
				position = point + (distance + Physics::Margin) * Vec3::Backward;
			}
		}

		return position;
	}

	Vec3 GetNormal(const Vec3& point, const Box& box)
	{
		// [HACK] ãHÇ…é∏îsÇ∑ÇÈÇÃÇ≈ÅAVec3::UpÇï‘Ç∑ÇÊÇ§Ç…ïœçX
		// assert(!box.intersects(point));

		if (point.y > box.y + box.h / 2)
		{
			return Vec3::Up;
		}
		else if (point.y < box.y - box.h / 2)
		{
			return Vec3::Down;
		}
		else if (point.x > box.x + box.w / 2)
		{
			return Vec3::Right;
		}
		else if (point.x < box.x - box.w / 2)
		{
			return Vec3::Left;
		}
		else if (point.z > box.z + box.d / 2)
		{
			return Vec3::Forward;
		}
		else if (point.z < box.z - box.d / 2)
		{
			return Vec3::Backward;
		}

		return Vec3::Up;
	}
}

namespace cre
{
	BoxCollider::BoxCollider(const Vec3& size, Physics::Group group) :
		Collider(group), m_offset(Vec3::Zero), m_size(size) {}

	BoxCollider::BoxCollider(const Vec3& offset, const Vec3& size, Physics::Group group) :
		Collider(group), m_offset(offset), m_size(size) {}

	void BoxCollider::init()
	{
		Collider::init();
		m_transform = entity()->transform();
	}

	Vec3 BoxCollider::setPosition(const Vec3& position)
	{
		return m_transform->setPosition(position - m_offset);
	}

	Vec3 BoxCollider::setCenter(const Vec3& center)
	{
		return setPosition(center - Vec3(0, m_size.y / 2, 0));
	}

	Vec3 BoxCollider::position() const
	{
		return m_transform->position() + m_offset;
	}

	bool BoxCollider::intersects(const Box& other) const
	{
		return other.intersects(Box(center(), m_size));
	}

	bool BoxCollider::intersects(const Ray& other) const
	{
		return other.intersects(Box(center(), m_size));
	}

	Optional<Vec3> BoxCollider::intersectsAt(const Ray& other) const
	{
		return other.intersectsAt(Box(center(), m_size));
	}

	bool BoxCollider::detectWall(const Box& body, const Vec3& direction) const
	{
		const auto box = this->box();

		// íÜÇ…ì¸Ç¡ÇƒÇµÇ‹Ç¡ÇΩéûÇÃèàóù.
		if (box.intersects(body.center))
		{
			return false;
		}

		return box.intersects(body.movedBy(direction));
	}

	void BoxCollider::extrude(const stupid_ptr<Rigidbody>& rigidbody) const
	{
		const Box box(center(), m_size + rigidbody->collider()->size());

		if (!box.intersects(rigidbody->collider()->center()))
		{
			return;
		}

		if (box.intersects(rigidbody->previousCenter()))
		{
			const auto position = Escape(rigidbody->collider()->center(), box);
			const auto normal = GetNormal(position, box);

			rigidbody->collider()->setCenter(position);
			rigidbody->addVelocity(-normal.dot(rigidbody->velocity()) * normal);

			return;
		}

		const auto direction = rigidbody->collider()->center() - rigidbody->previousCenter();
		const Ray ray(rigidbody->previousCenter(), direction.isZero() ? Vec3::Down : direction.normalized());
		auto distance = 0.0;

		ray.test(box, distance);

		const auto position = rigidbody->previousCenter() + ray.direction * (distance - Physics::Margin);
		const auto extra = rigidbody->collider()->center() - position;
		const auto normal = GetNormal(position, box);

		rigidbody->collider()->moveBy(-normal.dot(extra) * normal);
		rigidbody->addVelocity(-normal.dot(rigidbody->velocity()) * normal);
	}

# ifdef _DEBUG
	void BoxCollider::draw(double thickness, const Color& color) const
	{
		Figure::DrawBox(center(), m_size, thickness, color);
	}
# endif

	unique_ptr<Component> BoxCollider::Create(const XMLElement& element, const Assets&)
	{
		const auto offset = GetArg<Vec3>(element, L"offset", Vec3::Zero);
		const auto size = GetArg<Vec3>(element, L"size");
		const auto group = GetArg<Physics::Group>(element, L"group", Physics::Groups::Environment);

		if(!size || !offset || !group)
		{
			return nullptr;
		}

		return std::make_unique<BoxCollider>(offset.value(), size.value(), group.value());
	}
}
