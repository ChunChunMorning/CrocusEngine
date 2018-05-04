# include "UIManager.hpp"
# include <Siv3D.hpp>
# include "../Engine.hpp"
# include "../UI.hpp"

namespace cre
{
	using namespace s3d;

	using Type = std::pair<weak_ptr<IUI>, double>;

	void UIManager::update()
	{
		Erase_if(
			m_uis,
			[&](const Type& e) { return e.first.expired(); }
		);

		for (auto& ui : m_uis)
		{
			ui.second = ui.first.lock()->depth();
		}

		std::sort(
			m_uis.begin(),
			m_uis.end(),
			[](const Type& a, const Type& b) { return a.second > b.second; }
		);
	}

	void UIManager::draw() const
	{
		for (const auto& ui : m_uis)
		{
			ui.first.lock()->draw();
		}
	}

	void UIManager::Add(const weak_ptr<IUI>& ui)
	{
		Engine::GetUI()->m_uis.emplace_back(ui, 0.0);
	}
}
