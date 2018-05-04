# include "../CameraDepth.hpp"
# include "../Engine.hpp"
# include "GraphicsLayerManager.hpp"

using namespace s3d;

namespace cre
{
	CameraDepth::CameraDepth(const Vec3& position) :
		depth(position.dot({1, 0, 1})),
		level(CameraDepth::GetLevel(position)) {}

	int32 CameraDepth::GetLevel(const Vec3& position)
	{
		return Engine::GetLayer()->getLevel(position);
	}
}
