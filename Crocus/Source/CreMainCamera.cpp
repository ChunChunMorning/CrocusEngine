# include "../MainCamera.hpp"
# include "../Engine.hpp"
# include "MainCameraManager.hpp"

namespace cre
{
	using namespace s3d;

	namespace MainCamera
	{
		void SetPosition(const Vec3& position)
		{
			Engine::GetCamera()->setPos(position);
		}

		void SetTargetPosition(const Vec3& position)
		{
			Engine::GetCamera()->setTargetPos(position);
		}

		void SetScale(double scale)
		{
			Engine::GetCamera()->setScale(scale);
		}

		void SetTargetScale(double scale)
		{
			Engine::GetCamera()->setTargetScale(scale);
		}

		Vec2 GetPosition()
		{
			return Engine::GetCamera()->getPos();
		}

		Vec3 GetCurrentPosition()
		{
			return Engine::GetCamera()->getCurrentPos();
		}

		Vec3 GetTargetPosition()
		{
			return Engine::GetCamera()->getTargetPos();
		}

		double GetScale()
		{
			return Engine::GetCamera()->getScale();
		}

		double GetTargetScale()
		{
			return Engine::GetCamera()->getTargetScale();
		}

		RectF GetCameraArea()
		{
			return Engine::GetCamera()->getCameraArea();
		}
	}
}
