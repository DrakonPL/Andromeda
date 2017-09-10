#ifndef Logger_H
#define Logger_H

#include <string>
#include <sstream>

namespace Andromeda
{
	namespace Utils
	{
		#define Logger_Info( message,...)  Logger::Instance()->Info(__FILE__,__FUNCTION__,__LINE__,message,__VA_ARGS__)
		#define Logger_Error( message,...)  Logger::Instance()->Error(__FILE__,__FUNCTION__,__LINE__,message,__VA_ARGS__)

		class Logger
		{
		private:

			static Logger* _logger;
			
			bool _active;
			bool _debug;

			std::string _fileName;
			std::string _errorFileName;

			Logger();

			std::string GetTime();

			template <typename T>
			std::string to_string(T value)
			{
				//create an output string stream
				std::ostringstream os;

				//throw the value into the string stream
				os << value;

				//convert the string stream into a string and return
				return os.str();
			}

		public:

			static Logger* Instance();

			//log message 
			void Log(const char *message, ...);

			void Info( const char* file ,const char* function, int line, const char *message, ...);
			void Error(const char* file, const char* function, int line, const char *message, ...);

			void NetLog(const char *message, ...);
			
			//enable/disable logger
			void SetActive(bool state);
			
			//get logger state
			bool IsActive();
		};

	}
}

#endif
