#include "socket.hpp"
#include <system_error>
#include <WS2tcpip.h>
#include <iostream>
#include "cleansocket.h"
#include "clientsock.h"


int main() {
	AmthSocket::SocketImpl sock{};
	AmthSocket::ClientSocket clientSock{};

	CleanSocket tcpSocketIPV4( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	char origin[] = "www.google.com";

	std::cout << clientSock.sendGetRequestWithSocket(&tcpSocketIPV4,origin) << std::endl;

}



/*
	//SOCKET tcpSocketIPV6 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

	//udp sockets as well for ipv4 and ipv6
	SOCKET udpSocketIPV4 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKET udpSocketIPV6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

*/