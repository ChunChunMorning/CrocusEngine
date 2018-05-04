# pragma once
# include "UI.hpp"
# include "Updatable.hpp"

namespace cre
{
	class UpdatableUI : public Component, public IUI, public IUpdatable
	{
	public:

		void init() override;

		double depth() const override;
	};
}
