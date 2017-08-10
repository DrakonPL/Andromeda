#include <Andromeda/System/SystemManager.h>

namespace Andromeda
{
	namespace System
	{
		SystemManager* SystemManager::_systemManager = 0;

		SystemManager* SystemManager::Instance()
		{
			//initialize corerct version

			//return object
			return _systemManager;
		}


		SystemManager::SystemManager()
		{
			
		}


		PlatformTypeEnum SystemManager::GetPlatformType()
		{
			return _platformType;
		}
	}
}

