# include "UpdatableManager.hpp"
# include <algorithm>
# include "../Engine.hpp"
# include "../Updatable.hpp"

namespace cre
{
	void UpdatableManager::update()
	{
		auto& updatables = Engine::GetUpdatable()->m_updatables;

		updatables.erase(
			std::remove_if(updatables.begin(), updatables.end(), [&](const weak_ptr<IUpdatable>& e) { return e.expired(); }),
			updatables.end()
		);

		for (const auto& updatable : updatables)
		{
			updatable.lock()->update();
		}
	}

	void UpdatableManager::Add(const weak_ptr<IUpdatable>& updatable)
	{
		Engine::GetUpdatable()->m_updatables.push_back(updatable);
	}
}
