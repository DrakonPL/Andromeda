#ifndef Logger_H
#define Logger_H

#include <string>

namespace Andromeda
{
	namespace Utils
	{
		class Logger
		{
		private:

			static Logger* _logger;
			bool _active;
			std::string _fileName;

			Logger();

			std::string GetTime();

		public:

			static Logger* Instance();

			//log message 
			void Log(const char *message, ...);

			void NetLog(const char *message, ...);
			
			//enable/disable logger
			void SetActive(bool state);
			
			//get logger state
			bool IsActive();
		};

	}
}

#endif
