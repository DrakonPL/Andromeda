#ifndef StdioDirectory_H
#define StdioDirectory_H

#include <Andromeda/FileSystem/BaseDirectory.h>
#include <dirent.h>

namespace Andromeda
{
	namespace FileSystem
	{
		class FileManager;

		class StdioDirectory : public BaseDirectory
		{
		private:

			DIR* _directory;

		protected:

			StdioDirectory();
			StdioDirectory(std::string dirName);

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