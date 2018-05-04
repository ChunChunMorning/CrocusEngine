# pragma once
# include <Siv3D.hpp>

namespace cre
{
	namespace Coordinate
	{
		using namespace s3d;

		constexpr double PixelsPerUnit = 100.0;

		constexpr Vec2 Isometric(const Vec3& vector)
		{
			// Mat3x2::Rotate(Radians(-45))
			// Mat3x2 rot(0.70711f, -0.70711f, 0.70711f, 0.70711f, 0, 0);

			// Mat3x2::Scale({ Math::Cos(Math::Pi / 6.0) / Math::Cos(Math::Pi / 4.0), Math::Sin(Math::Pi / 6.0) / Math::Sin(Math::Pi / 4.0) })
			// Mat3x2 scale(1.22474f, 0, 0, 0.70711f, 0, 0);

			// (rot * scale).transform(Float2(vector.x, -vector.z));
			return Mat3x2(0.86603f, -0.5f, -0.86603f, -0.5f, 0, static_cast<float>(-vector.y)).transform(vector.xz());
		}

		constexpr Vec3 ToVec3(const Vec2& vector)
		{
			return{ vector.x, 0, vector.y };
		}

		constexpr Vec3 SetY(const Vec3& vector, double y)
		{
			return{ vector.x, y, vector.z };
		}

		constexpr Vec3 CancelY(const Vec3& vector)
		{
			return SetY(vector, 0);
		}

		inline double Angle(const Vec3& a, const Vec3& b)
		{
			return Math::Acos(a.dot(b) / (a.length() * b.length()));
		}

		inline double AngleFromNormal(const Vec3& normal, const Vec3& direction)
		{
			return Math::Acos(normal.dot(direction) / direction.length());
		}

		inline double AngleXZ(const Vec3& a, const Vec3& b)
		{
			return Angle(CancelY(a), CancelY(b));
		}

		inline double AngleFromNormalXZ(const Vec3& normal, const Vec3& direction)
		{
			return AngleFromNormal(normal, CancelY(direction));
		}

		Vec3 RotateAroundY(const Vec3& vector, double angle);

		std::pair<double, Vec3> Directionize(const Vec3& vector);
	}
}
