#ifndef WinSockNetworkManager_H
#define WinSockNetworkManager_H

#include <Andromeda/Network/NetworkManager.h>

#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

namespace Andromeda
{
	namespace Network
	{
		class WinSockNetworkManager : public NetworkManager
		{
		private:

			WSADATA wsa;

		public:

			~WinSockNetworkManager();

			bool Init();
			TcpSocket* GetTcpSocket(std::string name);
		};
	}
}

#endif
