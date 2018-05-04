# include "../Drawable.hpp"
# include "../Entity.hpp"
# include "DrawableManager.hpp"

namespace cre
{
	void Drawable::init()
	{
		DrawableManager::Add(entity()->findComponent(this));
	}
}
