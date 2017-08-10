#include <Andromeda/Network/WinSock/WinSockTcpSocket.h>
#include <Andromeda/Utils/Logger.h>

namespace Andromeda
{
	namespace Network
	{
		WinSockTcpSocket::WinSockTcpSocket(std::string name):TcpSocket()
		{
			_socket = socket(AF_INET, SOCK_STREAM, 0);

			if (_socket == INVALID_SOCKET)
			{
				Utils::Logger::Instance()->Log("Failed. Error Code : %d", WSAGetLastError());
				_created = false;
			}
			else
			{
				_created = true;
			}
		}

		WinSockTcpSocket::~WinSockTcpSocket()
		{
			if (_created)
			{
				closesocket(_socket);
			}			
		}

		bool WinSockTcpSocket::Connect(std::string ip, int port)
		{
			if (!_created)
			{
				return false;
			}

			_ip = ip;
			_port = port;

			_server.sin_addr.s_addr = inet_addr(_ip.c_str());
			_server.sin_family = AF_INET;
			_server.sin_port = htons(_port);

			//Connect to remote server
			if (connect(_socket, (struct sockaddr *)&_server, sizeof(_server)) < 0)
			{
				Utils::Logger::Instance()->Log("Connect error: %d", WSAGetLastError());
				return false;
			}

			_connected = true;

			return true;
		}

		bool WinSockTcpSocket::Send(char* data, int size)
		{
			if (!_connected)
			{
				return false;
			}

			if (send(_socket, data, size, 0) < 0)
			{
				Utils::Logger::Instance()->Log("Send error: %d", WSAGetLastError());
				return false;
			}

			return true;
		}

		int WinSockTcpSocket::Receive(char* data, int size)
		{
			if (!_connected)
			{
				return -1;
			}

			int recvSize = -1;

			if ((recvSize = recv(_socket, data, size, 0)) == SOCKET_ERROR)
			{
				Utils::Logger::Instance()->Log("Receive error: %d", WSAGetLastError());
				return -1;
			}

			return recvSize;
		}

		bool WinSockTcpSocket::Bind(int port)
		{
			if (!_created)
			{
				return false;
			}

			_ip = "127.0.0.1";
			_port = port;

			_server.sin_addr.s_addr = INADDR_ANY;
			_server.sin_family = AF_INET;
			_server.sin_port = htons(_port);

			if (bind(_socket, (struct sockaddr *)&_server, sizeof(_server)) == SOCKET_ERROR)
			{
				Utils::Logger::Instance()->Log("Bind failed with error code : %d", WSAGetLastError());
				return false;
			}

			_connected = true;

			return true;
		}

		bool WinSockTcpSocket::Listen(int connections)
		{
			if (!_created)
			{
				return false;
			}

			if (listen(_socket, 3) != 0)
			{
				Utils::Logger::Instance()->Log("Listen failed with error code : %d", WSAGetLastError());
				return false;
			}

			return true;
		}
	}
}