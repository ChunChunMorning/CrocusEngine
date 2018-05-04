# pragma once
# include "Drawable.hpp"
# include "Updatable.hpp"

namespace cre
{
	class UpdatableDrawer : public Component, public IUpdatable, public IDrawable
	{
	public:

		virtual ~UpdatableDrawer() = default;

		void init() override;
	};
}
