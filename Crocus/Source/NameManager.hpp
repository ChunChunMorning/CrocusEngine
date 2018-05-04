# pragma once
# include <vector>
# include "../Entity.hpp"
# include "../Pointer.hpp"

namespace cre
{
	class Name;

	class NameManager
	{
	private:

		std::vector<weak_ptr<Name>> m_names;

	public:

		static stupid_ptr<Entity> Find(const String& name);

		static Array<stupid_ptr<Entity>> FindEntities(const String& name);

		static void Add(const weak_ptr<Name>& name);
	};
}
