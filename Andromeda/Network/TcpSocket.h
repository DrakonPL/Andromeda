#ifndef TcpSocket_H
#define TcpSocket_H

#include <string>

namespace Andromeda
{
	namespace Network
	{
		class TcpSocket
		{
		protected:

			std::string _name;

			bool _created;
			bool _connected;

			std::string _ip;
			int _port;
		public:

			TcpSocket();
			virtual ~TcpSocket();

			virtual bool Connect(std::string ip, int port) = 0;
			virtual bool Send(char* data, int size) = 0;
			virtual int Receive(char* data, int size) = 0;
		};
	}
}

#endif
