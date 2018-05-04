# include "../World.hpp"
# include "../Engine.hpp"
# include "../Entity.hpp"
# include "../StringArgs.hpp"
# include "../Transform.hpp"
# include "LoaderManager.hpp"

namespace cre
{
	namespace World
	{
		void Add(shared_ptr<Entity>&& entity)
		{
			Engine::GetEntity()->addChild(std::move(entity));
		}

		unique_ptr<Entity> Create(const XMLElement& element, const Assets& assets)
		{
			auto entity = Entity::Create();
			auto child = element.firstChild();

# ifdef _DEBUG
			bool isEmpty = true;
# endif

			while (!child.isNull())
			{
				const auto lower = child.name().lower();

				if (lower == L"transform")
				{
					const auto position = GetArg<Vec3>(child, L"position", Vec3::Zero);

					if (position)
					{
						entity->transform().lock()->setLocalPosition(position.value());
					}
				}
				else if (lower == L"prefab")
				{
					const auto args = GetChildAsMap(child);

					auto prefab = assets.text(args.at(L"path"));

					for (const auto& arg : args)
					{
						if (arg.first == L"path")
						{
							continue;
						}

						prefab = prefab.replace(L'$' + arg.first, arg.second);
					}

					entity->addChild(Create(XMLReader(prefab).root(), assets), false);

# ifdef _DEBUG
					isEmpty = false;
# endif
				}
				else if (Engine::GetLoader()->isFactory(lower))
				{
					auto component = Engine::GetLoader()->getFactory(lower)(child, assets);

					if (component != nullptr)
					{
						entity->addComponent(std::move(component));

# ifdef _DEBUG
						isEmpty = false;
# endif
					}
				}
				else
				{
					entity->addChild(Create(child, assets), false);

# ifdef _DEBUG
					isEmpty = false;
# endif
				}

				child = child.nextSibling();
			}

# ifdef _DEBUG
			if (isEmpty)
			{
				LOG_ERROR(L"Loader ", element.name(), L"ÇÕãÛÇ≈Ç∑ÅB");
			}
# endif

			return entity;
		}
	}
}
