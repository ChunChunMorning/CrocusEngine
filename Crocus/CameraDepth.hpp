# pragma once
# include <Siv3D.hpp>

namespace cre
{
	class CameraDepth
	{
	public:

		double depth;

		int32 level;

		CameraDepth() = default;

		constexpr CameraDepth(double depth, int32 level) :
			depth(depth), level(level) {}

		constexpr CameraDepth(const Vec3& position, int32 level) :
			depth(position.dot({1, 0, 1})), level(level) {}

		CameraDepth(const Vec3& position);

		static double GetDepth(const Vec3& position)
		{
			return position.dot({ 1, 0, 1 });
		}

		static int32 GetLevel(const Vec3& position);
	};

	inline bool operator < (const CameraDepth& lhs, const CameraDepth& rhs)
	{
		return lhs.level == rhs.level ? lhs.depth < rhs.depth : lhs.level > rhs.level;
	}

	inline bool operator > (const CameraDepth& lhs, const CameraDepth& rhs)
	{
		return rhs < lhs;
	}

	inline bool operator <= (const CameraDepth& lhs, const CameraDepth& rhs)
	{
		return !(lhs > rhs);
	}

	inline bool operator >= (const CameraDepth& lhs, const CameraDepth& rhs)
	{
		return !(lhs < rhs);
	}
}
