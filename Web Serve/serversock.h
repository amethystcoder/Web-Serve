#pragma once
#include <string>
#include <system_error>
#include <WinSock2.h>
#include "cleansocket.h"
#include <iostream>

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
		void listenforConnections(CleanSocket* tcpSocketIPV4, const char ip_addr[], u_int port) {
			
			sockaddr_in hint{};
			hint.sin_family = AF_INET;
			hint.sin_addr.s_addr = INADDR_ANY;
			hint.sin_port = htons(port);

			//there is an issue with inet_pton here that i have to fix
			//inet_pton(AF_INET, ip_addr, &hint.sin_addr);

			int bind_result = bind(tcpSocketIPV4->Get(), reinterpret_cast<const sockaddr*>(&hint), sizeof(hint));

			if (bind_result == SOCKET_ERROR) {
				//try to prevent the use of throwing exceptions here
				throw std::system_error(WSAGetLastError(), std::system_category());
			}

			//bind should be successful at this stage

			int listen_result = listen(tcpSocketIPV4->Get(), SOMAXCONN);

			if (listen_result == SOCKET_ERROR) {
				//try to prevent the use of throwing exceptions here
				throw std::system_error(WSAGetLastError(), std::system_category());
			}
		}

		SOCKET acceptConnection(CleanSocket* tcpSocketIPV4) {
			sockaddr_in client{};
			int clientSize = sizeof(client);

			SOCKET clientSocket = accept(tcpSocketIPV4->Get(), reinterpret_cast<sockaddr*>(&client), &clientSize);

			if (clientSocket == INVALID_SOCKET) {
				//try to prevent the use of throwing exceptions here
				throw std::system_error(WSAGetLastError(), std::system_category());
			}

			return clientSocket;
		}

		std::string receiveData(SOCKET clientSocket) {
			char buf[4096];
			ZeroMemory(buf, 4096);

			int bytesReceived = recv(clientSocket, buf, 4096, 0);

			if (bytesReceived == SOCKET_ERROR) {
				throw std::system_error(WSAGetLastError(), std::system_category());
			}

			return std::string(buf, 0, bytesReceived);
		}

		inline void sendData(SOCKET &clientSocket,const char data[]) {
			int sendData = send(clientSocket, data, strlen(data) + 1, 0); 
			if (sendData == SOCKET_ERROR) {
				throw std::system_error(WSAGetLastError(), std::system_category());
			}
			Sleep(1000);
			shutdown(clientSocket, SD_SEND);  

		}


	private:
		int inet_pton(int af, const char* src, void* dst)
		{
			struct sockaddr_storage ss;
			int size = sizeof(ss);
			char src_copy[INET6_ADDRSTRLEN + 1];

			ZeroMemory(&ss, sizeof(ss));
			
			strncpy_s(src_copy, src, INET6_ADDRSTRLEN + 1);
			src_copy[INET6_ADDRSTRLEN] = 0;

			if (WSAStringToAddress(reinterpret_cast<WCHAR*>(src_copy), af, NULL, (struct sockaddr*)&ss, &size) == 0) {
				switch (af) {
				case AF_INET:
					*(struct in_addr*)dst = ((struct sockaddr_in*)&ss)->sin_addr;
					return 1;
				case AF_INET6:
					*(struct in6_addr*)dst = ((struct sockaddr_in6*)&ss)->sin6_addr;
					return 1;
				}
			}
			return 0;
		}

		const char* inet_ntop(int af, const void* src, char* dst, socklen_t size)
		{
			struct sockaddr_storage ss;
			unsigned long s = size;

			ZeroMemory(&ss, sizeof(ss));
			ss.ss_family = af;

			switch (af) {
			case AF_INET:
				((struct sockaddr_in*)&ss)->sin_addr = *(struct in_addr*)src;
				break;
			case AF_INET6:
				((struct sockaddr_in6*)&ss)->sin6_addr = *(struct in6_addr*)src;
				break;
			default:
				return NULL;
			}
			
			return (WSAAddressToString((struct sockaddr*)&ss, sizeof(ss), NULL, reinterpret_cast<WCHAR*>(dst), &s) == 0) ?
				dst : NULL;
		}
	};
}