# pragma once
# include "Component.hpp"

namespace cre
{
	class IUpdatable
	{
	public:

		virtual ~IUpdatable() = default;

		virtual void update() = 0;
	};

	class Updatable : public Component, public IUpdatable
	{
	public:

		virtual ~Updatable() = default;

		virtual void init() override;
	};
}
