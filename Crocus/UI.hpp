# pragma once
# include <Siv3D.hpp>
# include "Component.hpp"

namespace cre
{
	using namespace s3d;

	class IUI
	{
	public:

		virtual double depth() const = 0;

		virtual void draw() const = 0;
	};

	class UI : public Component, public IUI
	{
	public:

		void init() override;

		double depth() const override;
	};
}
