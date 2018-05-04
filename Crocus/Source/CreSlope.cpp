# include "Slope.hpp"
# include "../Coordinate.hpp"

namespace
{
	using namespace cre;

	bool IntersectsStrictly(const Triangle& a, const RectF& b)
	{
		// [HACK] éŒñ ìôÇ…ëŒâûÇ∑ÇÈÇΩÇﬂÇ…ëÂÇ´ÇﬂÇ…scaleÇê›íË
		const double scale = Coordinate::PixelsPerUnit * 100;

		const Triangle triangle(a.p0 * scale, a.p1 * scale, a.p2 * scale);
		const RectF rect(b.pos * scale, b.size * scale);

		return triangle.intersects(rect);
	}

	bool IntersectsStrictly(const RectF& a, const Triangle& b)
	{
		return IntersectsStrictly(b, a);
	}
}

namespace cre
{
	using Coordinate::Isometric;

	Plane Slope::spine() const
	{
		if (direction.x != 0)
		{
			const auto sign = Math::Sign(direction.x);

			return Plane(center + Vec3(sign * size.x / 2, 0, 0), size.yz(), Quaternion::Roll(-sign * Math::HalfPi));
		}

		const auto sign = Math::Sign(direction.z);

		return Plane(center + Vec3(0, 0, sign * size.z / 2), size.xy(), Quaternion::Pitch(sign * Math::HalfPi));
	}

	Plane Slope::hypotenuse() const
	{
		if (direction.x != 0)
		{
			const auto sign = Math::Sign(direction.x);

			return Plane(center, { Math::Sqrt(size.x * size.x + size.y * size.y), size.z }, Quaternion::Roll(sign * Math::Atan(size.y / size.x)));
		}

		const auto sign = Math::Sign(direction.z);

		return Plane(center, { size.x, Math::Sqrt(size.y * size.y + size.z * size.z) }, Quaternion::Pitch(-sign * Math::Atan(size.y / size.z)));
	}

	Triangle3D Slope::plus() const
	{
		if (direction.x != 0)
		{
			const auto sign = Math::Sign(direction.x);

			return Triangle3D(center + Vec3(-size.x, -size.y, size.z) / 2, center + Vec3(size.x, -size.y, size.z) / 2, center + Vec3(sign * size.x, size.y, size.z) / 2);
		}

		const auto sign = Math::Sign(direction.z);

		return Triangle3D(center + Vec3(size.x, -size.y, -size.z) / 2, center + Vec3(size.x, size.y, sign * size.z) / 2, center + Vec3(size.x, -size.y, size.z) / 2);
	}

	Triangle3D Slope::minus() const
	{
		if (direction.x != 0)
		{
			const auto sign = Math::Sign(direction.x);

			return Triangle3D(center + Vec3(-size.x, -size.y, -size.z) / 2, center + Vec3(sign * size.x, size.y, -size.z) / 2, center + Vec3(size.x, -size.y, -size.z) / 2);
		}

		const auto sign = Math::Sign(direction.z);

		return Triangle3D(center + Vec3(-size.x, -size.y, -size.z) / 2, center + Vec3(-size.x, -size.y, size.z) / 2, center + Vec3(-size.x, size.y, sign * size.z) / 2);
	}

	bool Slope::intersects(const Ray& other) const
	{
		return other.intersects(bottom()) ||
			other.intersects(spine()) ||
			other.intersects(hypotenuse()) ||
			other.intersects(plus()) ||
			other.intersects(minus());
	}
	
	bool Slope::intersects(const Box& other) const
	{
		if (!other.intersects(Box(center, size)))
		{
			return false;
		}

		if (direction.x != 0)
		{
			const auto sign = Math::Sign(direction.x);

			const auto rect = RectF(other.w, other.h).setCenter(other.center.xy());
			const auto triangle = Triangle(Vec2(-size.x, -size.y) / 2, Vec2(sign * size.x, size.y) / 2, Vec2(size.x, -size.y) / 2).movedBy(center.xy());

			return IntersectsStrictly(rect, triangle);
		}

		const auto sign = Math::Sign(direction.z);

		const auto rect = RectF(other.h, other.d).setCenter(other.center.yz());
		const auto triangle = Triangle(Vec2(-size.y, -size.z) / 2, Vec2(size.y, sign * size.z) / 2, Vec2(-size.y, size.z) / 2).movedBy(center.yz());

		return IntersectsStrictly(rect, triangle);
	}

	Optional<Vec3> Slope::intersectsAt(const Ray& other) const
	{
		Optional<Vec3> hitPos;
		Optional<Vec3> pos;
		double distance = Largest<double>();

		if (pos = other.intersectsAt(bottom()))
		{
			const auto d = other.origin.distanceFromSq(pos.value());

			if (d < distance)
			{
				distance = d;
				hitPos = pos;
			}
		}

		if (pos = other.intersectsAt(spine()))
		{
			const auto d = other.origin.distanceFromSq(pos.value());

			if (d < distance)
			{
				distance = d;
				hitPos = pos;
			}
		}

		if (pos = other.intersectsAt(hypotenuse()))
		{
			const auto d = other.origin.distanceFromSq(pos.value());

			if (d < distance)
			{
				distance = d;
				hitPos = pos;
			}
		}

		if (pos = other.intersectsAt(plus()))
		{
			const auto d = other.origin.distanceFromSq(pos.value());

			if (d < distance)
			{
				distance = d;
				hitPos = pos;
			}
		}

		if (pos = other.intersectsAt(minus()))
		{
			const auto d = other.origin.distanceFromSq(pos.value());

			if (d < distance)
			{
				distance = d;
				hitPos = pos;
			}
		}

		return hitPos;
	}
}
