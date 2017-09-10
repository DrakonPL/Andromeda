#include <Andromeda/Network/WinSock/WinSockNetworkManager.h>
#include <Andromeda/Network/WinSock/WinSockTcpSocket.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Network
	{
		WinSockNetworkManager::~WinSockNetworkManager()
		{
			WSACleanup();
		}

		bool WinSockNetworkManager::Init()
		{
			if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			{
				Utils::Logger_Info("Failed. Error Code : %d", WSAGetLastError());
				return false;
			}

			return true;
		}

		TcpSocket* WinSockNetworkManager::GetTcpSocket(std::string name)
		{
			return new WinSockTcpSocket(name);
		}
	}
}
