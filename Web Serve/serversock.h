#pragma once
#include <string>
#include <system_error>
#include <ws2def.h>
#include "cleansocket.h"

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
		void listenforConnections(CleanSocket* tcpSocketIPV4, char *ip_addr[], u_int port) {
			
			sockaddr_in hint{};
			hint.sin_family = AF_INET;
			hint.sin_port = htons(port);

			inet_pton(AF_INET, *ip_addr, &hint.sin_addr);

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

			SOCKET new_client_socket = accept(tcpSocketIPV4->Get(), nullptr,nullptr);
			//we need to check that the new_client_socket is valid
			if (new_client_socket == INVALID_SOCKET) {
				//try to prevent the use of throwing exceptions here
				throw std::system_error(WSAGetLastError(), std::system_category());
			}

			char buffer[4096];
			recv(new_client_socket, buffer, sizeof(buffer), 0);
			
			//this is a simple response
			char sendbuffer[4096] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Hello, World!</h1></body></html>";
			send(new_client_socket, sendbuffer, sizeof(sendbuffer), 0);

			//connect(tcpSocketIPV4->Get(), reinterpret_cast<const sockaddr*>(&hint), sizeof(hint));

			//freeaddrinfo();

			
		}


	private:
	};
}