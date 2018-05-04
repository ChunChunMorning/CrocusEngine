# include "../Assets.hpp"
# include "../EncryptAsset.hpp"
# include "../Savedata.hpp"

using namespace s3d;

namespace cre
{
	void AssetsLoader::start(const FilePath& path)
	{
		m_task.start([this, path]() {
# ifdef ENCRYPT_ASSET
			auto binary = Crypto2::DecryptFile(path, Savedata::Key());

			assert(binary.has_value());

			FileArchive archive;

			archive.open(std::move(binary.value()));
# else
			FileArchive archive(path);
# endif
			assert(archive.isOpened());

			for (const auto& content : archive.contents())
			{
				const auto extension = FileSystem::Extension(content);

				if (extension == L"png" || extension == L"wav")
				{
					m_binaryFiles.push(std::make_pair(FileSystem::FileName(content).lower(), archive.loadByteArray(content)));
				}
				else
				{
					const auto str = FileSystem::FileName(content);

					m_texts[FileSystem::FileName(content).lower()] = TextReader(archive.load(content)).readAll();
				}
			}
		});
	}

	void AssetsLoader::update(uint32 max)
	{
		if (isDone())
		{
			m_task.wait();
			return;
		}

		for (auto i = 0u; i < max; ++i)
		{
			BinaryFile binaryFile;

			if (m_binaryFiles.try_pop(binaryFile))
			{
				if (FileSystem::Extension(binaryFile.first) == L"png")
				{
					m_textures[binaryFile.first] = Texture(std::move(binaryFile.second));
				}
				else if (FileSystem::Extension(binaryFile.first) == L"wav")
				{
					m_sounds[binaryFile.first] = Sound(std::move(binaryFile.second));
				}
			}
		}
	}

	Assets AssetsLoader::create()
	{
		Assets assets(std::move(m_texts), std::move(m_textures), std::move(m_sounds));

		m_texts = {};
		m_textures = {};
		m_sounds = {};

		return assets;
	}
}
