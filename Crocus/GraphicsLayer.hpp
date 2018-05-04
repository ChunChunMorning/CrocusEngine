# pragma once
# include <Siv3D.hpp>
# include "Component.hpp"

namespace cre
{
	using namespace s3d;

	class IGraphicsLayer
	{
	public:

		virtual ~IGraphicsLayer() = default;

		virtual Box region() const = 0;

		virtual int32 level() const = 0;
	};

	class GraphicsLayer : public Component, public IGraphicsLayer
	{
	public:

		virtual ~GraphicsLayer() = default;

		void init() override;
	};
}
