# pragma once
# include <Siv3D.hpp>
# include "../Assets.hpp"
# include "../Component.hpp"
# include "../Pointer.hpp"

namespace cre
{
	class Transform;

	using Factory = std::function<unique_ptr<Component>(const XMLElement&, const Assets&)>;

	class Loader
	{
	public:

		enum class State
		{
			Unloaded, Loading, Loaded
		};

	private:

		State m_state;

		FilePath m_path;

		double m_stopwatch;

		Vec3 m_center;

		Vec3 m_size;

		weak_ptr<Transform> m_root;

		AssetsLoader m_assetsLoader;

# ifdef _DEBUG
		Assets m_assets;
# endif

	public:

		Loader::Loader(const FilePath& path, const Vec3& center, const Vec3& size);

		void update();

		bool notYet() const;
	};
}
