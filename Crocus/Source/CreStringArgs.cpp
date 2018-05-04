# include "../StringArgs.hpp"

using namespace s3d;

namespace cre
{
	Optional<XMLElement> FindChild(const XMLElement& element, const String& name)
	{
		const auto lower = name.lower();
		auto child = element.firstChild();

		while (!child.isNull())
		{
			if (child.name().lower() == lower)
			{
				return child;
			}

			child = child.nextSibling();
		}

		return none;
	}

	std::unordered_map<String, String > GetChildAsMap(const XMLElement& element)
	{
		auto child = element.firstChild();
		std::unordered_map<String, String > map;

		while (!child.isNull())
		{
# ifdef _DEBUG
			assert(map.find(child.name()) == map.end());
# endif

			map[child.name()] = child.text();
			child = child.nextSibling();
		}

		return map;
	}
}
