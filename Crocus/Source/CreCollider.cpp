# include "../Collider.hpp"
# include "../Engine.hpp"
# include "../Entity.hpp"
# include "ColliderManager.hpp"

using namespace s3d;

namespace cre
{
	void Collider::init()
	{
		Engine::GetCollider()->Add(entity()->findComponent(this));
	}
}
