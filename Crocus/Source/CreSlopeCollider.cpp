# include "../SlopeCollider.hpp"
# include "../BoxCollider.hpp"
# include "../Entity.hpp"
# include "../Figure.hpp"
# include "../Physics.hpp"
# include "../Rigidbody.hpp"
# include "../StringArgs.hpp"
# include "Slope.hpp"

using namespace s3d;

namespace
{
	using namespace cre;

	Vec3 GetNormal(const Vec3& point, const Box& box)
	{
		assert(!box.intersects(point));

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

		return Vec3::Backward;
	}

	double DistanceFromHypotenuse(const Box& box, const Slope& slope)
	{
		const std::array<Vec3, 4> vertexes = {
			box.center + Vec3(box.size.x, -box.size.y, box.size.z) / 2,
			box.center + Vec3(box.size.x, -box.size.y, -box.size.z) / 2,
			box.center + Vec3(-box.size.x, -box.size.y, -box.size.z) / 2,
			box.center + Vec3(-box.size.x, -box.size.y, box.size.z) / 2
		};

		double distance = 0;

		for (const auto& vertex : vertexes)
		{
			double d;

			if (Ray(vertex, Vec3::Up).test(slope.hypotenuse().scaled(10), d) && d > distance)
			{
				distance = Min(d, slope.center.y + slope.size.y / 2 - vertex.y);
			}
		}

		return distance;
	}

	void PutOnHypotenuse(const Slope& slope, double distance, const stupid_ptr<Rigidbody>& rigidbody)
	{
		rigidbody->collider()->setCenter(rigidbody->collider()->center() + Vec3::Up * (distance + Physics::Margin));

		const auto velocity = rigidbody->velocity();
		const auto normal = slope.hypotenuse().rotation * Vec3::Up;

		rigidbody->setVelocity({
			velocity.x * normal.x < 0 ? 0 : velocity.x,
			velocity.y * normal.y < 0 ? 0 : velocity.y,
			velocity.z * normal.z < 0 ? 0 : velocity.z
		});
	}

	void PutOnHypotenuse(const Slope& slope, const stupid_ptr<Rigidbody>& rigidbody)
	{
		PutOnHypotenuse(
			slope,
			DistanceFromHypotenuse(Box(rigidbody->collider()->center(), rigidbody->collider()->size()), slope),
			rigidbody
		);
	}

	void Escape(const Slope& slope, const stupid_ptr<Rigidbody>& rigidbody)
	{
		const auto point = rigidbody->collider()->center();
		const auto box = Box(slope.center, slope.size + rigidbody->collider()->size());
		auto distance = point.y - (box.center.y - box.h / 2);
		auto normal = Vec3::Down;

		if (point.x > box.center.x)
		{
			const auto d = box.center.x + box.w / 2 - point.x;

			if (d < distance)
			{
				distance = d;
				normal = Vec3::Right;
			}
		}
		else
		{
			const auto d = point.x - (box.center.x - box.w / 2);

			if (d < distance)
			{
				distance = d;
				normal = Vec3::Right;
			}
		}

		if (point.z > box.center.z)
		{
			const auto d = box.center.z + box.d / 2 - point.z;

			if (d < distance)
			{
				distance = d;
				normal = Vec3::Forward;
			}
		}
		else
		{
			const auto d = point.z - (box.center.z - box.d / 2);

			if (d < distance)
			{
				distance = d;
				normal = Vec3::Backward;
			}
		}

		const auto d = DistanceFromHypotenuse(Box(rigidbody->collider()->center(), rigidbody->collider()->size()), slope);

		if (d < distance)
		{
			return PutOnHypotenuse(slope, d, rigidbody);
		}

		rigidbody->collider()->setCenter(point + (distance + cre::Physics::Margin) * normal);
		rigidbody->addVelocity(-normal.dot(rigidbody->velocity()) * normal);
	}
}

namespace cre
{
	SlopeCollider::SlopeCollider(const Vec3& size, const Vec3& direction, Physics::Group group) :
		Collider(group), m_offset(Vec3::Zero), m_size(size), m_direction(direction) {}

	SlopeCollider::SlopeCollider(const Vec3& offset, const Vec3& size, const Vec3& direction, Physics::Group group) :
		Collider(group), m_offset(offset), m_size(size), m_direction(direction) {}

	void SlopeCollider::init()
	{
		Collider::init();
		m_transform = entity()->transform();
	}

	Vec3 SlopeCollider::position() const
	{
		return m_transform->position() + m_offset;
	}

	Vec3 SlopeCollider::groundNormal() const
	{
		return Slope(center(), m_size, m_direction).hypotenuse().rotation * Vec3::Up;
	}

	bool SlopeCollider::intersects(const Box& other) const
	{
		return Slope(center(), m_size, m_direction).intersects(other);
	}

	bool SlopeCollider::intersects(const Ray& other) const
	{
		return Slope(center(), m_size, m_direction).intersects(other);
	}

	Optional<Vec3> SlopeCollider::intersectsAt(const Ray& other) const
	{
		return Slope(center(), m_size, m_direction).intersectsAt(other);
	}

	bool SlopeCollider::detectWall(const Box& body, const Vec3& direction) const
	{
		const auto box = Box(center(), m_size);

		// íÜÇ…ì¸Ç¡ÇƒÇµÇ‹Ç¡ÇΩéûÇÃèàóù.
		if (box.intersects(body.center))
		{
			return false;
		}

		// direction == m_direction ÇæÇ¡ÇΩéûÇÃîªíË.
		if (Math::Acos(direction.dot(m_direction) / direction.length()) < Radians(5))
		{
			return false;
		}

		return box.intersects(body.movedBy(direction));
	}

	void SlopeCollider::extrude(const stupid_ptr<Rigidbody>& rigidbody) const
	{
		const auto slope = Slope(center(), m_size, m_direction);

		if (!slope.intersects(Box(rigidbody->collider()->center(), rigidbody->collider()->size())))
		{
			return;
		}

		if (slope.intersects(Box(rigidbody->previousCenter(), rigidbody->collider()->size())))
		{
			return Escape(slope, rigidbody);
		}

		const Box box(center(), m_size + rigidbody->collider()->size());
		const Ray ray(rigidbody->previousCenter(), (rigidbody->collider()->center() - rigidbody->previousCenter()).normalized());
		double distance;

		if (ray.test(box, distance) && distance > 0)
		{
			const auto position = rigidbody->previousCenter() + ray.direction * (distance - Physics::Margin);
			const auto extra = rigidbody->collider()->center() - position;
			const auto normal = GetNormal(position, box);

			if (normal != Vec3::Up && normal != -slope.direction)
			{
				rigidbody->collider()->moveBy(-normal.dot(extra) * normal);
				rigidbody->addVelocity(-normal.dot(rigidbody->velocity()) * normal);

				return;
			}
		}

		PutOnHypotenuse(slope, rigidbody);
	}

# ifdef _DEBUG
	void SlopeCollider::draw(double thickness, const Color& color) const
	{
		Figure::DrawSlope(center(), m_size, m_direction, thickness, color);
	}
# endif

	unique_ptr<Component> SlopeCollider::Create(const XMLElement& element, const Assets&)
	{
		const auto offset = GetArg<Vec3>(element, L"offset", Vec3::Zero);
		const auto size = GetArg<Vec3>(element, L"size");
		const auto direction = GetArg<Vec3>(element, L"direction");
		const auto group = GetArg<Physics::Group>(element, L"group", Physics::Groups::Environment);

		if (!size || !offset || !direction || !group)
		{
			return nullptr;
		}

		return std::make_unique<SlopeCollider>(offset.value(), size.value(), direction.value(), group.value());
	}
}
