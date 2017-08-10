#include <Andromeda/Network/NetworkManager.h>

#ifdef ANDROMEDA_PC
#include <Andromeda/Network/WinSock/WinSockNetworkManager.h>
#endif

namespace Andromeda
{
	namespace Network
	{
		NetworkManager *NetworkManager::_networkManager = 0;

		NetworkManager::NetworkManager()
		{
			
		}

		NetworkManager* NetworkManager::Instance()
		{
			if (_networkManager == 0)
			{
#ifdef ANDROMEDA_PC
				{
					_networkManager = new WinSockNetworkManager();
				}
#endif

				_networkManager->Init();
			}

			return _networkManager;
		}

		NetworkManager::~NetworkManager()
		{
			delete _networkManager;
		}
	}
}