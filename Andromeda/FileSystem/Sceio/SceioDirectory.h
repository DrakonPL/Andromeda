#ifndef SceioDirectory_H
#define SceioDirectory_H

#include <Andromeda/FileSystem/BaseDirectory.h>
#include <psp2/io/dirent.h>
#include <psp2/io/fcntl.h>

namespace Andromeda
{
	namespace FileSystem
	{
		class FileManager;

		class SceioDirectory : public BaseDirectory
		{
		private:

			SceUID _directory;

		protected:

			SceioDirectory();
			SceioDirectory(std::string dirName);

		public:

			bool Open();
			void Close();

			std::vector<std::string> GetFiles();
			std::vector<std::string> GetFiles(std::string extension);

			friend class FileManager;
		};
	}
}

#endif