# pragma once
# include <Siv3D.hpp>

namespace cre
{
	class Slope
	{
	public:

		Vec3 center;

		Vec3 size;

		Vec3 direction;

		Slope() = default;

		Slope(const Vec3& center, const Vec3& size, const Vec3& direction) :
			center(center), size(size), direction(direction)
		{
			assert(
				direction == Vec3::Right ||
				direction == Vec3::Left ||
				direction == Vec3::Forward ||
				direction == Vec3::Backward
			);
		}

		Plane bottom() const
		{
			return Plane(center + Vec3(0, size.y / -2, 0), size.xz(), Quaternion::Pitch(Math::Pi));
		}

		Plane spine() const;

		Plane hypotenuse() const;

		Triangle3D plus() const;

		Triangle3D minus() const;

		bool intersects(const Box& other) const;

		bool intersects(const Ray& other) const;

		Optional<Vec3> intersectsAt(const Ray& other) const;
	};
}
