# ifdef _DEBUG

# pragma once
# include <Siv3D.hpp>

namespace cre
{
	using namespace s3d;

	namespace Debug
	{
		bool IsActive();

		void Activate(bool isDebug);

		void Draw(const std::function<void()>& drawer);

		void DrawLine(const Vec3& p0, const Vec3& p1, double thickness, const Color& color);

		void DrawRect(const Vec3& center, const Vec2& size, double thickness, const Color& color);

		inline void DrawRect(const Vec3& center, const double size, double thickness, const Color& color)
		{
			DrawRect(center, { size, size }, thickness, color);
		}

		void DrawBox(const Box& box, double thickness, const Color& color);

		inline void DrawBox(const Vec3& center, const Vec3& size, double thickness, const Color& color)
		{
			DrawBox(Box(center, size), thickness, color);
		}

		void DrawCircle(const Vec3& center, double radius, double thickness, const Color& color);

		void DrawSphere(const Sphere& sphere, double thickness, const Color& color);

		inline void DrawSphere(const Vec3& center, double radius, double thickness, const Color& color)
		{
			DrawSphere(Sphere(center, radius), thickness, color);
		}
	}
}

# endif
