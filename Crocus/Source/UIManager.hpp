# pragma once
# include <vector>
# include "../Pointer.hpp"

namespace cre
{
	class IUI;

	class UIManager
	{
	private:

		std::vector<std::pair<weak_ptr<IUI>, double>> m_uis;

	public:

		void update();

		void draw() const;

		static void Add(const weak_ptr<IUI>& ui);
	};
}
