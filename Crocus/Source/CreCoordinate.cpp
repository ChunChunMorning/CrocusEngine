# include "../Coordinate.hpp"

using namespace s3d;

namespace cre
{
	namespace Coordinate
	{
		Vec3 RotateAroundY(const Vec3& vector, double angle)
		{
			const auto s = std::sin(angle);
			const auto c = std::cos(angle);
			return{ vector.x * c + vector.z * s, vector.y, vector.x * -s + vector.z * c };
		}

		std::pair<double, Vec3> Directionize(const Vec3& vector)
		{
			if (vector.isZero())
			{
				return{ 0.0, Vec3::Zero };
			}

			std::pair<double, Vec3> direction;

			direction.first = vector.length();
			direction.second = vector / direction.first;

			return direction;
		}
	}
}
