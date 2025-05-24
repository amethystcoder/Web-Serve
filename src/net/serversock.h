#ifndef SERVERSOCK_H

#define SERVERSOCK_H

#include <string>
#include <system_error>
#include <WinSock2.h>
#include "cleansocket.h"
#include <WS2tcpip.h>

namespace AmthSocket
{
	class ServerSocket
	{
		public:
			ServerSocket();
			~ServerSocket() noexcept;

			ServerSocket(const ServerSocket&) = delete;
			ServerSocket& operator = (const ServerSocket&) = delete;

			ServerSocket(ServerSocket&&) noexcept = default;
			ServerSocket& operator = (ServerSocket&&) noexcept = default;


			//ip_addr is the ip address of the server and looks like "127.0.0.1"
			void listenforConnections(CleanSocket* tcpSocketIPV4, const char ip_addr[], u_int port);

			SOCKET acceptConnection(CleanSocket* tcpSocketIPV4);

			std::string receiveData(SOCKET clientSocket);

			void sendData(SOCKET& clientSocket, const char data[]);


		private:
			int inet_pton(int af, const char* src, void* dst);
			const char* inet_ntop(int af, const void* src, char* dst, socklen_t size);
	};
}


#endif // !SERVERSOCK_H

