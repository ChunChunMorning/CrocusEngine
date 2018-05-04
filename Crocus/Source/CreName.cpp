# include "../Name.hpp"
# include "../Entity.hpp"
# include "../StringArgs.hpp"
# include "NameManager.hpp"

using namespace s3d;

namespace cre
{
	void Name::init()
	{
		NameManager::Add(entity()->findComponent(this));
	}

	stupid_ptr<Entity> Name::Find(const String& name)
	{
		return NameManager::Find(name);
	}

	Array<stupid_ptr<Entity>> Name::FindEntities(const String& name)
	{
		return NameManager::FindEntities(name);
	}

	unique_ptr<Component> Name::Create(const XMLElement& element, const Assets&)
	{
		const auto name = GetArg<String>(element, L"name");

		if (!name)
		{
			return nullptr;
		}

		return std::make_unique<Name>(name.value());
	}
}
