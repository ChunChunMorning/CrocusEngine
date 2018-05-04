# pragma once
# include <vector>
# include "../CameraDepth.hpp"
# include "../Pointer.hpp"

namespace cre
{
	class IDrawable;

	class DrawableManager
	{
	private:

		int32 m_currentLevel;

		double m_seconds;

		std::vector<std::pair<weak_ptr<IDrawable>, CameraDepth>> m_drawables;

	public:

		DrawableManager();

		void update();

		void draw() const;

		static void Add(const weak_ptr<IDrawable>& drawable);
	};
}
