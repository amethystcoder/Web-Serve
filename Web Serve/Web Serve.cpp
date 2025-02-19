#include "socket.hpp"
#include <system_error>
#include <iostream>
#include <WS2tcpip.h>
#include <Winsock2.h>
#include "cleansocket.h"
#include "clientsock.h"
#include "serversock.h"


int main() {
	AmthSocket::SocketImpl sock{};
	//AmthSocket::ClientSocket clientSock{};

	AmthSocket::ServerSocket serverSock{};

	CleanSocket tcpSocketIPV4( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	char origin[] = "www.google.com";

	//std::cout << clientSock.sendGetRequestWithSocket(&tcpSocketIPV4,origin) << std::endl;

	char ip_addr[] = "127.0.0.1";

	std::cout << "client is now listening on port 5400" << std::endl;
	serverSock.listenforConnections(&tcpSocketIPV4, ip_addr, 5400);
	SOCKET clientSocket = serverSock.acceptConnection(&tcpSocketIPV4);
	std::cout << serverSock.receiveData(clientSocket) << std::endl;
	serverSock.sendData(clientSocket, "HTTP/1.1 200 OK\nContent-Type: text/html\n\n<html><body><h1>Hello, World!</h1></body></html>");
}


/*
	//SOCKET tcpSocketIPV6 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

	//udp sockets as well for ipv4 and ipv6
	SOCKET udpSocketIPV4 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKET udpSocketIPV6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

*/