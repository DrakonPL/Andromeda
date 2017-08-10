#include <Andromeda/FileSystem/Sceio/SceioDirectory.h>
#include <Andromeda/Utils/Logger.h>
#include <string.h>

namespace Andromeda
{
	namespace FileSystem
	{
		SceioDirectory::SceioDirectory() : BaseDirectory()
		{
			_directory = 0;
		}

		SceioDirectory::SceioDirectory(std::string dirName) : BaseDirectory(dirName)
		{
			_directory = 0;
		}

		bool SceioDirectory::Open()
		{
			_directory = sceIoDopen(_dirName.c_str());

			if (_directory > 0)
			{
				return true;
			}

			return false;
		}

		void SceioDirectory::Close()
		{
			if (_directory > 0)
			{
				sceIoDclose(_directory);
			}
		}

		std::vector<std::string> SceioDirectory::GetFiles()
		{
			std::vector<std::string> files;

			if (_directory > 0)
			{
				SceIoDirent dirent;
				memset(&dirent, 0, sizeof(dirent));

				while (sceIoDread(_directory, &dirent) > 0)
				{
					//if (SCE_SO_ISDIR(dirent.d_stat.st_mode))
					{
						files.push_back(dirent.d_name);
					}
				}

				sceIoDclose(_directory);
				_directory = sceIoDopen(_dirName.c_str());

			}

			return files;
		}

		std::vector<std::string> SceioDirectory::GetFiles(std::string extension)
		{
			std::vector<std::string> allFiles = GetFiles();
			std::vector<std::string> files;

			for (size_t i = 0; i < allFiles.size(); i++)
			{
				if (allFiles[i].find(extension) != std::string::npos)
				{
					files.push_back(allFiles[i]);
				}
			}

			return files;
		}

	}
}