#ifndef WinSockTcpSocket_H
#define WinSockTcpSocket_H

#include <Andromeda/Network/TcpSocket.h>
#include <winsock2.h>


namespace Andromeda
{
	namespace Network
	{
		class WinSockTcpSocket : public TcpSocket
		{
		private:

			SOCKET _socket;
			sockaddr_in _server;

		public:

			WinSockTcpSocket(std::string name);
			~WinSockTcpSocket();

			bool Connect(std::string ip, int port);

			bool Send(char* data, int size);
			int Receive(char* data, int size);

			bool Bind(int port);
			bool Listen(int connections);


		};
	}
}

#endif
