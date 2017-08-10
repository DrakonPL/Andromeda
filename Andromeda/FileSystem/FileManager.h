#ifndef FileManager_H
#define FileManager_H

#include <Andromeda/FileSystem/BaseFile.h>
#include <Andromeda/FileSystem/BaseDirectory.h>
#include <string>

namespace Andromeda
{
	namespace FileSystem
	{
		class FileManager
		{
		private:

			std::string _mainDirPath;
			std::string _saveDirPath;

			static FileManager* _instance;

			FileManager();
			FileManager(std::string dirPath);

		public:

			static FileManager* Instance();

			//set main location of file system
			void SetMainDirPath(std::string pathName);
			
			//get main location of file system
			std::string GetMainDirPath();

			void SetSaveDirPath(std::string pathName);

			std::string GetSaveDirPath();

			//get directory
			BaseDirectory* GetDirectory(std::string fileName);

			//check if file exists
			bool FileExists(std::string fileName);

			//get file
			BaseFile *GetFile(std::string fileName, bool saveLocation = false);

		};
	}
}

#endif
