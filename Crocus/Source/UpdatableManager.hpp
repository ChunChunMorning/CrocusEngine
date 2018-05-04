# pragma once
# include <vector>
# include "../Pointer.hpp"

namespace cre
{
	class IUpdatable;

	class UpdatableManager
	{
	private:

		std::vector<weak_ptr<IUpdatable>> m_updatables;

	public:

		void update();

		static void Add(const weak_ptr<IUpdatable>& updatable);
	};
}
