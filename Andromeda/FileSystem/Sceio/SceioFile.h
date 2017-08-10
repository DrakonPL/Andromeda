#ifndef SceioFile_H
#define SceioFile_H

#include <Andromeda/FileSystem/BaseFile.h>
#include <psp2/display.h>

namespace Andromeda
{
	namespace FileSystem
	{
		class FileManager;

		class SceioFile : protected BaseFile
		{
		private:

			SceUID _filBuf;

		protected:

			SceioFile();
			SceioFile(std::string fileName, std::string loadFileName);

		public:			

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