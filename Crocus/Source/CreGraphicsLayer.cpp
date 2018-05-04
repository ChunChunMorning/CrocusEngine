# include "../GraphicsLayer.hpp"
# include "../Entity.hpp"
# include "GraphicsLayerManager.hpp"

using namespace s3d;

namespace cre
{
	void GraphicsLayer::init()
	{
		GraphicsLayerManager::Add(entity()->findComponent(this));
	}
}
