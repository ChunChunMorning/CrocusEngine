# ifdef _DEBUG

# include "../Debug.hpp"
# include "../Engine.hpp"
# include "../Figure.hpp"
# include "DebugManager.hpp"

using namespace s3d;

namespace cre
{
	namespace Debug
	{
		bool IsActive()
		{
			return Engine::GetDebug()->isActive();
		}

		void Activate(bool isDebug)
		{
			Engine::GetDebug()->activate(isDebug);
		}

		void Draw(const std::function<void()>& drawer)
		{
			Engine::GetDebug()->add(drawer);
		}

		void DrawLine(const Vec3& p0, const Vec3& p1, double thickness, const Color& color)
		{
			Engine::GetDebug()->add(
				[=]() { Figure::DrawLine(p0, p1, thickness, color); }
			);
		}

		void DrawRect(const Vec3& center, const Vec2& size, double thickness, const Color& color)
		{
			Engine::GetDebug()->add(
				[=]() { Figure::DrawRect(center, size, thickness, color); }
			);
		}

		void DrawBox(const Box& box, double thickness, const Color& color)
		{
			Engine::GetDebug()->add(
				[=]() { Figure::DrawBox(box, thickness, color); }
			);
		}

		void DrawCircle(const Vec3& center, double radius, double thickness, const Color& color)
		{
			Engine::GetDebug()->add(
				[=]() { Figure::DrawCircle(center, radius, thickness, color); }
			);
		}

		void DrawSphere(const Sphere& sphere, double thickness, const Color& color)
		{
			Engine::GetDebug()->add(
				[=]() { Figure::DrawSphere(sphere, thickness, color); }
			);
		}
	}
}

# endif
