# include "../Physics.hpp"
# include "../Collider.hpp"
# include "../Engine.hpp"
# include "ColliderManager.hpp"

using namespace s3d;

namespace cre
{
	namespace Physics
	{
		weak_ptr<Collider> Detect(const Box& box, Group mask)
		{
			return Engine::GetCollider()->detect(box, mask);
		}

		weak_ptr<Collider> Detect(const Ray& ray, Group mask)
		{
			return Engine::GetCollider()->detect(ray, mask);
		}

		Array<weak_ptr<Collider>> DetectAll(const Box& box, Group mask)
		{
			return Engine::GetCollider()->detectAll(box, mask);
		}

		Array<weak_ptr<Collider>> DetectAll(const Ray& ray, Group mask)
		{
			return Engine::GetCollider()->detectAll(ray, mask);
		}

		std::pair<weak_ptr<Collider>, Vec3> DetectAt(const Ray& ray, Group mask, double length)
		{
			return Engine::GetCollider()->detectAt(ray, mask, length);
		}

		Array<std::pair<weak_ptr<Collider>, Vec3>> DetectAtAll(const Ray& ray, Group mask, double length)
		{
			return Engine::GetCollider()->detectAtAll(ray, mask, length);
		}

		bool DetectWall(const Box& body, const Vec3& direction, Group mask)
		{
			return Engine::GetCollider()->detectWall(body, direction, mask);
		}
	}
}
