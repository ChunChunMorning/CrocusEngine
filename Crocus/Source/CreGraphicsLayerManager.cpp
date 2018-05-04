# include "GraphicsLayerManager.hpp"
# include "../Coordinate.hpp"
# include "../Engine.hpp"
# include "../Figure.hpp"
# include "../GraphicsLayer.hpp"

using namespace s3d;

namespace cre
{
	void GraphicsLayerManager::erase()
	{
		Erase_if(
			m_layers,
			[](const weak_ptr<IGraphicsLayer>& e) { return e.expired(); }
		);
	}

	int32 GraphicsLayerManager::getLevel(const Vec3& position)
	{
		Optional<int32> level;

		for (const auto& layer : m_layers)
		{
			const auto lay = layer.lock();

			if (lay->region().intersects(position) && lay->level() > level)
			{
				level = lay->level();
			}
		}

		return level.value_or(0);
	}

# ifdef _DEBUG
	void GraphicsLayerManager::draw() const
	{
		for (const auto& layer : m_layers)
		{
			const auto lay = layer.lock();

			Figure::DrawBox(lay->region(), 1 / Coordinate::PixelsPerUnit, Palette::Pink);
		}
	}
# endif

	void GraphicsLayerManager::Add(const weak_ptr<IGraphicsLayer>& layer)
	{
		Engine::GetLayer()->m_layers.push_back(layer);
	}
}
