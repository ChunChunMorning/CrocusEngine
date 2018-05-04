# pragma once
# include <Siv3D.hpp>
# include "PhysicsGroup.hpp"
# include "Pointer.hpp"

namespace cre
{
	using namespace s3d;

	class Collider;

	namespace Physics
	{
		constexpr double Margin = 0.001;

		constexpr Vec3 Gravity = { 0, -9.81, 0 };

		weak_ptr<Collider> Detect(const Box& box, Group mask);

		weak_ptr<Collider> Detect(const Ray& ray, Group mask);

		Array<weak_ptr<Collider>> DetectAll(const Box& box, Group mask);

		Array<weak_ptr<Collider>> DetectAll(const Ray& ray, Group mask);

		std::pair<weak_ptr<Collider>, Vec3> DetectAt(const Ray& ray, Group mask, double length = Largest<double>());

		Array<std::pair<weak_ptr<Collider>, Vec3>> DetectAtAll(const Ray& ray, Group mask, double length = Largest<double>());

		bool DetectWall(const Box& body, const Vec3& direction, Group mask);
	}
}
