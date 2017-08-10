#include <Andromeda/FileSystem/Sceio/SceioFile.h>
#include <psp2/io/fcntl.h>
#include <stdio.h>

namespace Andromeda
{
	namespace FileSystem
	{
		SceioFile::SceioFile() : BaseFile()
		{
			_filBuf = 0;
		}

		SceioFile::SceioFile(std::string fileName, std::string loadFileName) : BaseFile(fileName, loadFileName)
		{
			_filBuf = 0;
		}

		bool SceioFile::Open(FileMode fileMode, FileType fileType)
		{
			if(fileMode == FileSystem::Read)
			{
				_filBuf = sceIoOpen(_loadFileName.c_str(), SCE_O_RDONLY, 0777);
			}
			else if (fileMode == FileSystem::Write)
			{
				_filBuf = sceIoOpen(_loadFileName.c_str(), SCE_O_WRONLY | SCE_O_CREAT, 0777);
			}
			else
			{
				_filBuf = sceIoOpen(_loadFileName.c_str(), SCE_O_APPEND | SCE_O_WRONLY | SCE_O_CREAT, 0777);
			}

			if (_filBuf < 0)
			{
				return false;
			}

			return true;
		}

		void SceioFile::Close()
		{
			if (_filBuf >= 0)
				sceIoClose(_filBuf);
		}

		bool SceioFile::Exist()
		{
			if (_filBuf >= 0)
				return true;

			return false;
		}

		void SceioFile::Read(void *data, unsigned int size, int count)
		{
			sceIoRead(_filBuf,data, size * count);
		}

		void SceioFile::Write(void *data, unsigned int size, int count)
		{
			sceIoWrite(_filBuf, data, size * count);
		}

		unsigned char* SceioFile::GetData(int &dataSize)
		{
			if (_filBuf != 0)
			{
				dataSize = sceIoLseek(_filBuf, 0, SEEK_END);
				//dataSize = ftell(_filBuf);
				sceIoLseek(_filBuf, 0, SEEK_SET);

				unsigned char* buffer = new unsigned char[dataSize];

				sceIoRead(_filBuf,buffer, dataSize);

				return buffer;
			}

			return 0;
		}

		char* SceioFile::GetTextData(int &dataSize)
		{
			if (_filBuf != 0)
			{
				dataSize = sceIoLseek(_filBuf, 0, SEEK_END);
				//dataSize = ftell(_filBuf);
				sceIoLseek(_filBuf, 0, SEEK_SET);

				char *buffer = new char[dataSize + 1];
				sceIoRead(_filBuf, buffer, dataSize);

				buffer[dataSize] = '\0';

				return buffer;
			}

			return 0;
		}
	}
}
