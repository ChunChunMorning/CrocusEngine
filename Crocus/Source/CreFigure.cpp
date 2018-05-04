# include "../Figure.hpp"
# include <Siv3D.hpp>
# include "../Coordinate.hpp"

using namespace s3d;

namespace cre
{
	namespace Figure
	{
		using Coordinate::Isometric;

		void DrawLine(const Vec3& p0, const Vec3& p1, double thickness, const Color& color)
		{
			Line(Isometric(p0), Isometric(p1)).draw(thickness, color);
		}

		void DrawRect(const Vec3& center, const Vec2& size, double thickness, const Color& color)
		{
			const std::array<Vec3, 4> vertexes = { {
				center + Vec3(size.x / 2, 0, size.y / 2),
				center + Vec3(size.x / 2, 0, -size.y / 2),
				center + Vec3(-size.x / 2, 0, -size.y / 2),
				center + Vec3(-size.x / 2, 0, size.y / 2)
			} };

			Line(Isometric(vertexes[0]), Isometric(vertexes[1])).draw(thickness, color);
			Line(Isometric(vertexes[1]), Isometric(vertexes[2])).draw(thickness, color);
			Line(Isometric(vertexes[2]), Isometric(vertexes[3])).draw(thickness, color);
			Line(Isometric(vertexes[3]), Isometric(vertexes[0])).draw(thickness, color);
		}

		void DrawBox(const Box& box, double thickness, const Color& color)
		{
			const std::array<Vec3, 7> vertexes = { {
				box.center + Vec3(box.w / 2, box.h / 2, box.d / 2),
				box.center + Vec3(box.w / 2, box.h / 2, -box.d / 2),
				box.center + Vec3(-box.w / 2, box.h / 2, -box.d / 2),
				box.center + Vec3(-box.w / 2, box.h / 2, box.d / 2),
				box.center + Vec3(box.w / 2, -box.h / 2, -box.d / 2),
				box.center + Vec3(-box.w / 2, -box.h / 2, -box.d / 2),
				box.center + Vec3(-box.w / 2, -box.h / 2, box.d / 2)
			} };

			Line(Isometric(vertexes[0]), Isometric(vertexes[1])).draw(thickness, color);
			Line(Isometric(vertexes[1]), Isometric(vertexes[2])).draw(thickness, color);
			Line(Isometric(vertexes[2]), Isometric(vertexes[3])).draw(thickness, color);
			Line(Isometric(vertexes[3]), Isometric(vertexes[0])).draw(thickness, color);
			Line(Isometric(vertexes[1]), Isometric(vertexes[4])).draw(thickness, color);
			Line(Isometric(vertexes[2]), Isometric(vertexes[5])).draw(thickness, color);
			Line(Isometric(vertexes[3]), Isometric(vertexes[6])).draw(thickness, color);
			Line(Isometric(vertexes[4]), Isometric(vertexes[5])).draw(thickness, color);
			Line(Isometric(vertexes[5]), Isometric(vertexes[6])).draw(thickness, color);
		}

		void DrawCircle(const Vec3& center, double radius, double thickness, const Color& color)
		{
			Ellipse(Isometric(center), 1.22474 * radius, 0.70711 * radius).drawFrame(thickness, 0, color);
		}

		void DrawSphere(const Sphere& sphere, double thickness, const Color& color)
		{
			Ellipse(Isometric(sphere.center), 1.22474 * sphere.r, 0.70711 * sphere.r).drawFrame(thickness, 0, color);
			Circle(Isometric(sphere.center), 1.22474 * sphere.r).drawFrame(thickness, 0, color);
		}

		void DrawSlope(const Vec3& center, const Vec3& size, const Vec3& direction, double thickness, const Color& color)
		{
			assert(
				direction == Vec3::Right ||
				direction == Vec3::Left ||
				direction == Vec3::Forward ||
				direction == Vec3::Backward
			);

			if (direction == Vec3::Right)
			{
				std::array<Vec3, 5> vertexes = {
					center + Vec3(-size.x, -size.y, size.z) / 2,
					center + Vec3(-size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, size.y, -size.z) / 2,
					center + Vec3(size.x, size.y, size.z) / 2
				};

				Line(Isometric(vertexes[0]), Isometric(vertexes[1])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[2])).draw(thickness, color);
				Line(Isometric(vertexes[0]), Isometric(vertexes[4])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[3])).draw(thickness, color);
				Line(Isometric(vertexes[2]), Isometric(vertexes[3])).draw(thickness, color);
				Line(Isometric(vertexes[3]), Isometric(vertexes[4])).draw(thickness, color);
			}
			else if (direction == Vec3::Left)
			{
				std::array<Vec3, 6> vertexes = {
					center + Vec3(-size.x, -size.y, size.z) / 2,
					center + Vec3(-size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, -size.y, size.z) / 2,
					center + Vec3(-size.x, size.y, -size.z) / 2,
					center + Vec3(-size.x, size.y, size.z) / 2
				};

				Line(Isometric(vertexes[0]), Isometric(vertexes[1])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[2])).draw(thickness, color);
				Line(Isometric(vertexes[2]), Isometric(vertexes[3])).draw(thickness, color);
				Line(Isometric(vertexes[0]), Isometric(vertexes[5])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[4])).draw(thickness, color);
				Line(Isometric(vertexes[2]), Isometric(vertexes[4])).draw(thickness, color);
				Line(Isometric(vertexes[3]), Isometric(vertexes[5])).draw(thickness, color);
				Line(Isometric(vertexes[4]), Isometric(vertexes[5])).draw(thickness, color);
			}
			else if (direction == Vec3::Forward)
			{
				std::array<Vec3, 5> vertexes = {
					center + Vec3(-size.x, -size.y, size.z) / 2,
					center + Vec3(-size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, -size.y, -size.z) / 2,
					center + Vec3(-size.x, size.y, size.z) / 2,
					center + Vec3(size.x, size.y, size.z) / 2
				};

				Line(Isometric(vertexes[0]), Isometric(vertexes[1])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[2])).draw(thickness, color);
				Line(Isometric(vertexes[0]), Isometric(vertexes[3])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[3])).draw(thickness, color);
				Line(Isometric(vertexes[2]), Isometric(vertexes[4])).draw(thickness, color);
				Line(Isometric(vertexes[3]), Isometric(vertexes[4])).draw(thickness, color);
			}
			else
			{
				std::array<Vec3, 6> vertexes = {
					center + Vec3(-size.x, -size.y, size.z) / 2,
					center + Vec3(-size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, -size.y, -size.z) / 2,
					center + Vec3(size.x, -size.y, size.z) / 2,
					center + Vec3(-size.x, size.y, -size.z) / 2,
					center + Vec3(size.x, size.y, -size.z) / 2
				};

				Line(Isometric(vertexes[0]), Isometric(vertexes[1])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[2])).draw(thickness, color);
				Line(Isometric(vertexes[3]), Isometric(vertexes[0])).draw(thickness, color);
				Line(Isometric(vertexes[0]), Isometric(vertexes[4])).draw(thickness, color);
				Line(Isometric(vertexes[1]), Isometric(vertexes[4])).draw(thickness, color);
				Line(Isometric(vertexes[2]), Isometric(vertexes[5])).draw(thickness, color);
				Line(Isometric(vertexes[3]), Isometric(vertexes[5])).draw(thickness, color);
				Line(Isometric(vertexes[4]), Isometric(vertexes[5])).draw(thickness, color);
			}
		}
	}
}
