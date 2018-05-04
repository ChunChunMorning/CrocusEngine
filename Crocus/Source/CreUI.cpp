# include "../UI.hpp"
# include "../Entity.hpp"
# include "../Transform.hpp"
# include "UIManager.hpp"

namespace cre
{
	void UI::init()
	{
		UIManager::Add(entity()->findComponent(this));
	}

	double UI::depth() const
	{
		return entity()->transform().lock()->position().z;
	}
}
