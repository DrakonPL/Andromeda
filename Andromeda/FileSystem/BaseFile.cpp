#include <Andromeda/FileSystem/BaseFile.h>

namespace Andromeda
{
	namespace FileSystem
	{
		BaseFile::BaseFile():_fileName(""), _loadFileName("")
		{
			_fileName = "";
			_loadFileName = "";

			_loaded = false;
		}

		BaseFile::BaseFile(std::string fileName, std::string loadFileName)
		{
			_fileName = fileName;
			_loadFileName = loadFileName;

			_loaded = false;
		}

		BaseFile::~BaseFile()
		{

		}
	}
}
