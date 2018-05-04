# include "NameManager.hpp"
# include "../Engine.hpp"
# include "../Name.hpp"

namespace
{
	constexpr size_t MaxSize = 10000;
}

namespace cre
{
	stupid_ptr<Entity> NameManager::Find(const String& name)
	{
		Erase_if(Engine::GetName()->m_names, [](const weak_ptr<Name>& e) { return e.expired(); });

		for (const auto& comp : Engine::GetName()->m_names)
		{
# ifdef _DEBUG
			if (comp.expired())
			{
				continue;
			}
# endif

			const auto ptr = comp.lock();

			if (ptr->name() == name)
			{
				return ptr->entity();
			}
		}

		return nullptr;
	}

	Array<stupid_ptr<Entity>> NameManager::FindEntities(const String& name)
	{
		Erase_if(Engine::GetName()->m_names, [](const weak_ptr<Name>& e) { return e.expired(); });

		Array<stupid_ptr<Entity>> result;

		for (const auto& comp : Engine::GetName()->m_names)
		{
			const auto ptr = comp.lock();

			if (ptr->name() == name)
			{
				result.push_back(ptr->entity());
			}
		}

		return result;
	}

	void NameManager::Add(const weak_ptr<Name>& name)
	{
		Engine::GetName()->m_names.push_back(name);

		// [TODO] ‰i‰“‚Æ’Ç‰Á‚³‚ê‚½Žž‚ÉƒNƒ‰ƒbƒVƒ…‚·‚é‚Ì‚ð–h‚®‚½‚ß.
		if (Engine::GetName()->m_names.size() > MaxSize)
		{
			Erase_if(Engine::GetName()->m_names, [](const weak_ptr<Name>& e) { return e.expired(); });

			assert(!"NameManager's size is more than MaxSize.");
		}
	}
}
