# include "../Updatable.hpp"
# include "../Entity.hpp"
# include "UpdatableManager.hpp"

namespace cre
{
	void Updatable::init()
	{
		UpdatableManager::Add(entity()->findComponent(this));
	}
}
