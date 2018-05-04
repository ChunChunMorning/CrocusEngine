# include "LoaderManager.hpp"
# include "../Engine.hpp"

// Factory
# include "../BoxCollider.hpp"
# include "../Name.hpp"
# include "../Rigidbody.hpp"
# include "../SlopeCollider.hpp"

using namespace s3d;

namespace cre
{
	LoaderManager::LoaderManager()
	{
		CSVReader csvReader(L"/1001");

		for (auto i = 0u; i < csvReader.rows; ++i)
		{
			m_loaderRegions[csvReader.get<String>(i, 0)] = Box(
				csvReader.get<Vec3>(i, 1), csvReader.get<Vec3>(i, 2)
			);
		}

		m_factories[L"boxcollider"] = BoxCollider::Create;
		m_factories[L"name"] = Name::Create;
		m_factories[L"slopecollider"] = SlopeCollider::Create;
		m_factories[L"rigidbody"] = Rigidbody::Create;
	}

	void LoaderManager::update()
	{
		for (auto& loader : m_loaders)
		{
			loader->update();
		}
	}

	void LoaderManager::add(const FilePath& path)
	{
		const auto filename = FileSystem::FileName(path);

		for (const auto& loaderRegion : m_loaderRegions)
		{
			if (filename == loaderRegion.first)
			{
				m_loaders.push_back(std::make_unique<Loader>(path, loaderRegion.second.center, loaderRegion.second.size));
			}
		}
	}

	void LoaderManager::addFactory(const String& name, const Factory& factory)
	{
		m_factories[name.lower()] = factory;
	}

	Factory LoaderManager::getFactory(const String& name) const
	{
		return m_factories.at(name.lower());
	}

	bool LoaderManager::isFactory(const String& name) const
	{
		return m_factories.find(name) != m_factories.end();
	}

	bool LoaderManager::notYet() const
	{
		return AnyOf(m_loaders, [](const unique_ptr<Loader>& e) { return e->notYet(); });
	}
}
