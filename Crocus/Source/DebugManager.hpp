# ifdef _DEBUG

# pragma once
# include "../Coordinate.hpp"
# include "../Figure.hpp"
# include "../MainCamera.hpp"

namespace cre
{
	using Drawer = std::function<void()>;

	class DebugManager
	{
	private:

		bool m_isActive;

		Array<Drawer> m_drawers;

	public:

		DebugManager() : m_isActive(false) {}

		void activate(bool isActive)
		{
			m_isActive = isActive;
		}

		void add(const Drawer& drawer)
		{
			if (m_isActive)
			{
				m_drawers.push_back(drawer);
			}
		}

		void drawGrid() const
		{
			const Point center(
				static_cast<int32>(MainCamera::GetTargetPosition().x),
				static_cast<int32>(MainCamera::GetTargetPosition().z)
			);

			for (auto x = -10; x < 10; ++x)
			{
				for (auto z = -10; z < 10; ++z)
				{
					Figure::DrawRect(
						{ center.x + x + 0.5, 0, center.y + z + 0.5 },
						1,
						1 / Coordinate::PixelsPerUnit,
						Color(Palette::Gray, 50)
					);
				}
			}
		}

		void draw()
		{
			for (const auto& drawer : m_drawers)
			{
				drawer();
			}

			m_drawers.clear();
		}

		bool isActive() const
		{
			return m_isActive;
		}
	};
}

# endif
