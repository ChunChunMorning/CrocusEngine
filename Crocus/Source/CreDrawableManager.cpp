# include "DrawableManager.hpp"
# include <Siv3D.hpp>
# include "../Engine.hpp"
# include "../Drawable.hpp"
# include "MainCameraManager.hpp"

namespace cre
{
	using Type = std::pair<weak_ptr<IDrawable>, CameraDepth>;

	DrawableManager::DrawableManager() :m_currentLevel(0), m_seconds(0) {}

	void DrawableManager::update()
	{
		const auto level = CameraDepth::GetLevel(Engine::GetCamera()->getCurrentPos());

		auto& drawables = Engine::GetDrawable()->m_drawables;

		Erase_if(
			drawables,
			[&](const Type& e) { return e.first.expired(); }
		);

		for (auto& drawable : m_drawables)
		{
			const auto ptr = drawable.first.lock();

			drawable.second = ptr->depth();

			if (drawable.second.level - level > 50)
			{
				ptr->setAlpha(Max(0.0, ptr->alpha() - DeltaTime::GetDeltaTime()));
			}
			else
			{
				ptr->setAlpha(Min(1.0, ptr->alpha() + DeltaTime::GetDeltaTime()));
			}
		}

		std::sort(
			drawables.begin(),
			drawables.end(),
			[](const Type& a, const Type& b) { return a.second > b.second; }
		);
	}

	void DrawableManager::draw() const
	{
		for (const auto& drawable : Engine::GetDrawable()->m_drawables)
		{
			const auto ptr = drawable.first.lock();

			if (ptr->isActive())
			{
				ptr->draw();
			}
		}
	}

	void DrawableManager::Add(const weak_ptr<IDrawable>& drawable)
	{
		Engine::GetDrawable()->m_drawables.emplace_back(drawable, CameraDepth{});
	}
}
