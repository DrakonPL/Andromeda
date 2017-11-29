#ifndef DiskFile_H
#define DiskFile_H

#include <Andromeda/FileSystem/BaseFile.h>

namespace Andromeda
{
	namespace FileSystem
	{
		class FileManager;

		class StdioFile : public BaseFile
		{
		private:

			FILE* _filBuf;

		protected:

			StdioFile();
			StdioFile(std::string fileName, std::string loadFileName);

		public:

			~StdioFile();

			bool Open(FileMode fileMode, FileType fileType);
			void Close();

			bool Exist();
			
			void Read(void* data, unsigned size, int count);
			void Write(void *data, unsigned int size, int count);

			unsigned char* GetData(int& dataSize);
			char* GetTextData(int &dataSize);

			friend class FileManager;
		};
	}
}

#endif