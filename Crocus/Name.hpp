# pragma once
# include <Siv3D.hpp>
# include "Assets.hpp"
# include "Component.hpp"

namespace cre
{
	using namespace s3d;

	class Name : public Component
	{
	private:

		String m_name;

	public:

		Name(const String& name) : m_name(name) {}

		void init() override;

		const String& name() const { return m_name; }

		static stupid_ptr<Entity> Find(const String& name);

		static Array<stupid_ptr<Entity>> FindEntities(const String& name);

		static unique_ptr<Component> Create(const XMLElement& element, const Assets&);
	};
}
