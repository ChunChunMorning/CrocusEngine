# include "Loader.hpp"
# include "../EncryptAsset.hpp"
# include "../Engine.hpp"
# include "../Entity.hpp"
# include "../DeltaTime.hpp"
# include "../MainCamera.hpp"
# include "../Pointer.hpp"
# include "../Savedata.hpp"
# include "../StringArgs.hpp"
# include "../Transform.hpp"
# include "../World.hpp"
# include "LoaderManager.hpp"

using namespace s3d;

namespace
{
	constexpr auto LoadingDelay = 3.0;
}

namespace cre
{
	Loader::Loader(const FilePath& path, const Vec3& center, const Vec3& size) :
		m_state(State::Unloaded), m_path(path), m_stopwatch(0), m_center(center), m_size(size)
	{
		//Println(m_center, L" , ", m_size);
// [HACK] 事前計算したものを使用
//# ifdef ENCRYPT_ASSET
//		auto binary = Crypto2::DecryptFile(m_path, Savedata::Key());
//
//		assert(binary.has_value());
//
//		FileArchive archive;
//
//		archive.open(std::move(binary.value()));
//# else
//		FileArchive archive(path);
//# endif
//		assert(archive.isOpened());
//
//		const XMLReader reader(archive.load(FileSystem::BaseName(m_path) + L"/index.xml"));
//
//		assert(reader.isValid());
//
//		auto minOffset = Vec3(0, -1000000, 0);
//		auto maxOffset = Vec3(0, 1000000, 0);
//		auto child = reader.root().firstChild();
//
//		while (!child.isNull())
//		{
//			const auto name = child.name().lower();
//
//			if (name == L"transform")
//			{
//				const auto position = GetArg<Vec3>(child, L"position");
//
//				if (position)
//				{
//					m_center = position.value();
//				}
//			}
//			else if (name == L"boxcollider")
//			{
//				const auto offset = GetArg<Vec3>(child, L"offset");
//				const auto size = GetArg<Vec3>(child, L"size");
//
//				if (offset && size)
//				{
//					if (maxOffset.x < offset.value().x + size.value().x / 2)
//					{
//						maxOffset.x = offset.value().x + size.value().x / 2;
//					}
//					if (minOffset.x > offset.value().x - size.value().x / 2)
//					{
//						minOffset.x = offset.value().x - size.value().x / 2;
//					}
//					if (maxOffset.z < offset.value().z + size.value().z / 2)
//					{
//						maxOffset.z = offset.value().z + size.value().z / 2;
//					}
//					if (minOffset.z > offset.value().z - size.value().z / 2)
//					{
//						minOffset.z = offset.value().z - size.value().z / 2;
//					}
//				}
//			}
//
//			child = child.nextSibling();
//		}
//
//		m_center += (minOffset + maxOffset) / 2;
//		m_size = maxOffset - minOffset;
	}

	void Loader::update()
	{
		if (Box(m_center, m_size).scaled(3).intersects(MainCamera::GetCurrentPosition()))
		{
			m_stopwatch = LoadingDelay;
		}
		else
		{
			m_stopwatch = Max(0.0, m_stopwatch - DeltaTime::GetUnscaledDeltaTime());
		}

		switch (m_state)
		{
		case State::Unloaded:
			if (m_stopwatch >= LoadingDelay)
			{
				m_assetsLoader.start(m_path);
				m_state = State::Loading;
				LOG_DEBUG(L"Loader " + FileSystem::FileName(m_path) + L"のロードを開始します。");
			}
			break;

		case State::Loading:
			m_assetsLoader.update();

			if (m_assetsLoader.isDone())
			{
				const auto assets = m_assetsLoader.create();

# ifdef _DEBUG
				m_assets = assets;
# endif

				const XMLReader index(assets.text(L"index.xml"), XMLDocumentType::Text);

				auto entity = World::Create(index.root(), assets);
				m_root = entity->transform();
				World::Add(std::move(entity));

				m_state = State::Loaded;

				LOG_DEBUG(L"Loader " + FileSystem::FileName(m_path) + L"のロードが完了しました。");
			}
			break;

		case State::Loaded:
			if (m_stopwatch <= 0)
			{
				assert(!m_root.expired());

				m_root.lock()->entity()->remove();
				m_state = State::Unloaded;

				LOG_DEBUG(L"Loader " + FileSystem::FileName(m_path) + L"をアンロードしました。");
			}
# ifdef _DEBUG
			if (Input::KeyR.clicked && FileSystem::BaseName(m_path) != L"global")
			{
				assert(!m_root.expired());

				m_root.lock()->entity()->remove();

				const XMLReader index(L"Assets/" + FileSystem::BaseName(m_path) + L".xml");

				auto entity = World::Create(index.root(), m_assets);
				m_root = entity->transform();
				World::Add(std::move(entity));

				LOG_DEBUG(L"Loader " + FileSystem::FileName(m_path) + L"をリロードしました。");
			}
# endif
			break;
		}
	}

	bool Loader::notYet() const
	{
		return Box(m_center, m_size).intersects(MainCamera::GetCurrentPosition()) && m_state != State::Loaded;
	}
}
