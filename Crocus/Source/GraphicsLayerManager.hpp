# pragma once
# include <Siv3D.hpp>
# include "../Pointer.hpp"

namespace cre
{
	using namespace s3d;

	class IGraphicsLayer;

	class GraphicsLayerManager
	{
	private:

		Array<weak_ptr<IGraphicsLayer>> m_layers;

	public:

		void erase();

		int32 getLevel(const Vec3& position);

# ifdef _DEBUG
		void draw() const;
# endif

		static void Add(const weak_ptr<IGraphicsLayer>& layer);
	};
}
