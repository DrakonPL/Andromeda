#ifndef NetworkManager_H
#define NetworkManager_H

#include <Andromeda/Network/TcpSocket.h>

#include <string>


namespace Andromeda
{
	namespace Network
	{
		class NetworkManager
		{
		protected:

			static NetworkManager *_networkManager;

			NetworkManager();

		public:

			static NetworkManager* Instance();

			virtual ~NetworkManager();

			virtual bool Init() = 0;
			virtual TcpSocket* GetTcpSocket(std::string name) = 0;
		};
	}
}

#endif
