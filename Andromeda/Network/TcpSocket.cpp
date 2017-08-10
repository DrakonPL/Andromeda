#include <Andromeda/Network/TcpSocket.h>

namespace Andromeda
{
	namespace Network
	{
		TcpSocket::TcpSocket()
		{
			_created = false;
			_connected = false;
			_name = "";
			_port = -1;
		}

		TcpSocket::~TcpSocket()
		{
			
		}
	}
}
