# pragma once
# include <Siv3D.hpp>

namespace cre
{
	using namespace s3d;

	namespace Savedata
	{
		AES128Key Key();

		FilePath Path();

		Optional<String> Load(const FilePath& filename);

		bool Save(const FilePath& filename, const String& content);
	}
}
