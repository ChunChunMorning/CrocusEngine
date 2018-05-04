# pragma once
# include <unordered_map>
# include <Siv3D.hpp>
# include "Loader.hpp"

namespace cre
{
	using namespace s3d;

	class LoaderManager
	{
	private:

		Array<unique_ptr<Loader>> m_loaders;

		std::unordered_map<String, Box> m_loaderRegions;

		std::unordered_map<String, Factory> m_factories;

	public:

		LoaderManager();

		void update();

		void add(const FilePath& path);

		void addFactory(const String& name, const Factory& factory);

		Factory getFactory(const String& name) const;

		bool isFactory(const String& name) const;

		bool notYet() const;
	};
}
