#ifndef BaseFile_H
#define BaseFile_H

#include <string>

namespace Andromeda
{
	namespace FileSystem
	{
		enum FileMode
		{
			Read,
			Write,
			Append
		};

		enum FileType
		{
			Text,
			Binary
		};

		class FileManager;

		class BaseFile
		{
		public:

			std::string _fileName;
			std::string _loadFileName;

			bool _loaded;

			BaseFile();
			BaseFile(std::string fileName, std::string loadFileName);

		public:

			virtual ~BaseFile();

			bool IsLoaded() { return _loaded; }

			virtual bool Open(FileMode fileMode, FileType fileType) = 0;
			virtual void Close() = 0;

			virtual bool Exist() = 0;

			virtual void Read(void *data, unsigned int size, int count) = 0;
			virtual void Write(void *data, unsigned int size, int count) = 0;

			virtual unsigned char* GetData(int &dataSize) = 0;
			virtual char* GetTextData(int &dataSize) = 0;

			friend class FileManager;
		};
	}
}

#endif