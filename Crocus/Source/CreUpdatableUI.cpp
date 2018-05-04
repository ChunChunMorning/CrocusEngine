# include "../UpdatableUI.hpp"
# include "../Entity.hpp"
# include "../Transform.hpp"
# include "UIManager.hpp"
# include "UpdatableManager.hpp"

namespace cre
{
	void UpdatableUI::init()
	{
		UIManager::Add(entity()->findComponent(this));
		UpdatableManager::Add(entity()->findComponent(this));
	};

	double UpdatableUI::depth() const
	{
		return entity()->transform().lock()->position().z;
	}
}
