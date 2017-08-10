#include <Andromeda/Utils/Logger.h>

#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <Andromeda/FileSystem/FileManager.h>

#ifdef ANDROMEDA_VITA

//#include "debugnet.h"
//#define ip_server "192.168.0.12"
//#define port_server 18194
//int ret;
#endif

namespace Andromeda
{
	namespace Utils
	{
		Logger* Logger::_logger = 0;

		Logger::Logger()
		{
			_active = true;

			//create filename
			_fileName = "Log" + GetTime() + ".txt";

			#ifdef ANDROMEDA_VITA
			{
				//ret = debugNetInit(ip_server, port_server, DEBUG);
			}
			#endif
		}

		Logger* Logger::Instance()
		{
			if (_logger == 0)
			{
				_logger = new Logger();
			}

			return _logger;
		}

		void Logger::Log(const char* message, ...)
		{
			if (_active)
			{
				va_list argList;
				char cbuffer[1024];
				va_start(argList, message);
				vsnprintf(cbuffer, 1024, message, argList);
				va_end(argList);

				#ifdef ANDROMEDA_VITA
				{
					//debugNetPrintf(DEBUG, cbuffer, ret);
				}
				#endif

				FileSystem::BaseFile* file = FileSystem::FileManager::Instance()->GetFile(_fileName,true);

				if (file == 0)
					return;

				file->Open(FileSystem::Append, FileSystem::Text);
				file->Write(cbuffer, sizeof(char), strlen(cbuffer));
				file->Close();

				delete file;
			}
		}

		void Logger::NetLog(const char *message, ...)
		{
			va_list argList;
			char cbuffer[1024];
			va_start(argList, message);
			vsnprintf(cbuffer, 1024, message, argList);
			va_end(argList);

			#ifdef ANDROMEDA_VITA
			{
				//debugNetPrintf(DEBUG, cbuffer, ret);
			}
			#endif
		}

		void Logger::SetActive(bool state)
		{
			_active = state;
		}

		bool Logger::IsActive()
		{
			return _active;
		}

		std::string Logger::GetTime()
		{
			time_t     now = time(0);
			struct tm  tstruct;
			char       buf[80];
			tstruct = *localtime(&now);
			// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
			// for more information about date/time format
			strftime(buf, sizeof(buf), "%Y_%m_%d_%H_%M_%S", &tstruct);

			return buf;
		}

	}
}
