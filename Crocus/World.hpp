# pragma once
# include <Siv3D.hpp>
# include "Assets.hpp"
# include "Entity.hpp"
# include "Pointer.hpp"

namespace cre
{
	namespace World
	{
		void Add(shared_ptr<Entity>&& entity);

		unique_ptr<Entity> Create(const XMLElement& element, const Assets& assets);
	}
}
