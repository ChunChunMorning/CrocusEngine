# pragma once
# include <unordered_map>
# include <Siv3D.hpp>
# include "BlockingQueue.hpp"
# include "Task.hpp"

namespace cre
{
	using namespace s3d;

	class Assets
	{
	private:

		std::unordered_map<String, String> m_texts;

		std::unordered_map<String, Texture> m_textures;

		std::unordered_map<String, Sound> m_sounds;

	public:

		Assets() = default;

		Assets(
			std::unordered_map<String, String>&& text,
			std::unordered_map<String, Texture>&& textures,
			std::unordered_map<String, Sound>&& sounds
		) :
			m_texts(std::move(text)), m_textures(std::move(textures)), m_sounds(std::move(sounds)) {}


		void add(const String& key, const String& text)
		{
			m_texts[key.lower()] = text;
		}

		void add(const String& key, const Texture& texture)
		{
			m_textures[key.lower()] = texture;
		}

		void add(const String& key, const Sound& sound)
		{
			m_sounds[key.lower()] = sound;
		}

		String text(const String& key) const
		{
			return m_texts.at(key.lower());
		}

		INIReader ini(const String& key) const
		{
			const auto data = ToUTF8(text(key));

			return INIReader(ByteArray(data.data(), sizeof(decltype(data)::value_type) * data.length()));
		}

		CSVReader csv(const String& key) const
		{
			const auto data = ToUTF8(text(key));

			return CSVReader(ByteArray(data.data(), sizeof(decltype(data)::value_type) * data.length()));
		}

		XMLReader xml(const String& key) const
		{
			return XMLReader(text(key), XMLDocumentType::Text);
		}

		const std::unordered_map<String, String>& texts() const { return m_texts; }

		Texture texture(const String& key) const
		{
			return m_textures.at(key.lower());
		}

		const std::unordered_map<String, Texture>& textures() const { return m_textures; }

		Sound sound(const String& key) const
		{
			return m_sounds.at(key.lower());
		}

		const std::unordered_map<String, Sound>& sounds() const { return m_sounds; }
	};

	class AssetsLoader : private Uncopyable
	{
	private:

		using BinaryFile = std::pair<FilePath, ByteArray>;

		BlockingQueue<BinaryFile> m_binaryFiles;

		std::unordered_map<String, String> m_texts;

		std::unordered_map<String, Texture> m_textures;

		std::unordered_map<String, Sound> m_sounds;

		Task m_task;

	public:

		void start(const FilePath& path);
		
		void update(uint32 max = 1);

		bool isDone()
		{
			return m_task.isDone() && m_binaryFiles.empty();
		}

		Assets create();
	};
}
