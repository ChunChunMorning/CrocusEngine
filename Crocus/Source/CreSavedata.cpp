# include "../Savedata.hpp"
# include <shlobj.h>

using namespace s3d;

namespace cre
{
	namespace Savedata
	{
		AES128Key Key()
		{
			return AES128Key(0, 0, 0, 0);
		}

		FilePath Path()
		{
# ifndef _DEBUG
			wchar path[MAX_PATH];

			if (SHGetSpecialFolderPath(NULL, path, CSIDL_APPDATA, true))
				return Format(path, L"/AppName/");
# endif
			return L"Savedata/";
		}

		Optional<String> Load(const FilePath& filename)
		{
			if (!FileSystem::Exists(Savedata::Path() + filename))
			{
				return none;
			}

# ifndef _DEBUG
			BinaryReader reader(Savedata::Path() + filename);

			if (!reader)
			{
				return none;
			}

			return Crypto2::DecryptString(reader.readWhole(), Savedata::Key());
# else
			TextReader reader(Savedata::Path() + L"d_" + filename);

			if (!reader)
			{
				return none;
			}

			return reader.readAll();
# endif
		}

		bool Save(const FilePath& filename, const String& content)
		{
# ifndef _DEBUG
			BinaryWriter writer(Savedata::Path() + filename);

			if (!writer)
			{
				return false;
			}

			const auto pos = writer.write(Crypto2::EncryptString(content, Savedata::Key()));

			return pos != 0;
# else
			TextWriter writer(Savedata::Path() + L"d_" + filename);

			if (!writer)
			{
				return false;
			}

			writer.write(content);

			return true;
# endif
		}
	}
}
