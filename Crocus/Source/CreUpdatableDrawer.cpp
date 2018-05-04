# include "../UpdatableDrawer.hpp"
# include "../Entity.hpp"
# include "DrawableManager.hpp"
# include "UpdatableManager.hpp"

namespace cre
{
	void UpdatableDrawer::init()
	{
		UpdatableManager::Add(entity()->findComponent(this));
		DrawableManager::Add(entity()->findComponent(this));
	}
}
