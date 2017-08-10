#include <Andromeda/FileSystem/BaseDirectory.h>

namespace Andromeda
{
	namespace FileSystem
	{
		BaseDirectory::BaseDirectory()
		{
			_dirName = "";
		}

		BaseDirectory::BaseDirectory(std::string dirName)
		{
			_dirName = dirName;
		}
	}
}
