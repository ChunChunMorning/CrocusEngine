# pragma once
# include <Siv3D.hpp>
# include "Coordinate.hpp"

namespace cre
{
	using namespace s3d;

	namespace MainCamera
	{
		void SetPosition(const Vec3& position);

		void SetTargetPosition(const Vec3& position);

		void SetScale(double scale);

		void SetTargetScale(double scale);

		Vec2 GetPosition();

		Vec3 GetCurrentPosition();

		Vec3 GetTargetPosition();

		double GetScale();

		double GetTargetScale();

		RectF GetCameraArea();
	}
}
