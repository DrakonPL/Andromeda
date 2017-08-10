#include <Andromeda/FileSystem/FileManager.h>
#include <Andromeda/Utils/Logger.h>

#ifdef ANDROMEDA_PC
#include <Andromeda/FileSystem/Stdio/StdioFile.h>
#include <Andromeda/FileSystem/Stdio/StdioDirectory.h>
#endif

#ifdef ANDROMEDA_VITA
#include <Andromeda/FileSystem/Sceio/SceioFile.h>
#include <Andromeda/FileSystem/Sceio/SceioDirectory.h>
#endif

namespace Andromeda
{
	namespace FileSystem
	{
		FileManager* FileManager::_instance = 0;

		FileManager::FileManager()
		{
			_mainDirPath = "";
			_instance = 0;			
		}

		FileManager::FileManager(std::string dirPath)
		{
			_mainDirPath = "";
			_instance = 0;
		}

		FileManager* FileManager::Instance()
		{
			if (_instance == 0)
			{
				_instance = new FileManager();
			}

			return _instance;
		}

		//set main location of file system
		void FileManager::SetMainDirPath(std::string pathName)
		{
			_mainDirPath = pathName;
		}

		//get main location of file system
		std::string FileManager::GetMainDirPath()
		{
			return _mainDirPath;
		}

		void FileManager::SetSaveDirPath(std::string pathName)
		{
			_saveDirPath = pathName;
		}

		std::string FileManager::GetSaveDirPath()
		{
			return _saveDirPath;
		}

		//get directory
		BaseDirectory* FileManager::GetDirectory(std::string fileName)
		{
			std::string loadName = _mainDirPath + fileName;
			BaseDirectory* directory;

			#ifdef ANDROMEDA_PC
			{
				directory = new StdioDirectory(loadName);
			}
			#endif

			#ifdef ANDROMEDA_VITA
			{
				directory = new SceioDirectory(loadName);
			}
			#endif
			
			return directory;
		}

		//check if file exists
		bool FileManager::FileExists(std::string fileName)
		{
			bool exist = false;

			BaseFile* file = GetFile(fileName);

			file->Open(Read, Binary);

			exist = file->Exist();

			file->Close();

			return exist;
		}

		//get file
		BaseFile *FileManager::GetFile(std::string fileName, bool saveLocation)
		{
			std::string loadName = "";

			if (saveLocation)
			{
				loadName = _saveDirPath + fileName;
			}
			else
			{
				loadName = _mainDirPath + fileName;
			}

			BaseFile* newFile;

			#ifdef ANDROMEDA_PC
			{
				newFile = new StdioFile(fileName, loadName);
			}
			#endif

			#ifdef ANDROMEDA_VITA
			{
				newFile = new SceioFile(fileName, loadName);
			}
			#endif
			
			 
			return newFile;
		}
	}
}
