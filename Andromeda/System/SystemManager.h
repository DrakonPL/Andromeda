#ifndef SystemManager_H
#define SystemManager_H

#include <Andromeda/System/SystemEnums.h>
#include <string>

namespace Andromeda
{
	namespace System
	{
		class SystemManager
		{
		protected:

			static SystemManager *_systemManager;

			SystemManager();


			PlatformTypeEnum _platformType;

		public:

			static SystemManager* Instance();			

			PlatformTypeEnum GetPlatformType();

		};
	}
}

#endif