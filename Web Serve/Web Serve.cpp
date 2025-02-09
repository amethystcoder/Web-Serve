#include "socket.hpp"
#include <system_error>
#include <WS2tcpip.h>
#include <iostream>

class CleanSocket {
public:
    CleanSocket(int address_family, int sockettype, int protocol) {
        cleanSocket = socket(address_family, sockettype, protocol);
		std::cout << cleanSocket << std::endl;
        if (cleanSocket == INVALID_SOCKET) {
            throw std::system_error(WSAGetLastError(), std::system_category());
        }
    }

    SOCKET Get() const noexcept {
        return cleanSocket;
    }

	CleanSocket(const CleanSocket&) = delete;
	CleanSocket& operator = (const CleanSocket&) = delete;

    CleanSocket(CleanSocket&& rhs) noexcept :
        cleanSocket{ std::exchange(rhs.cleanSocket, INVALID_SOCKET) }
    {}

	CleanSocket& operator = (CleanSocket&& rhs) noexcept {
		if (cleanSocket != INVALID_SOCKET) {
			std::ignore = closesocket(cleanSocket);
		}
        
		cleanSocket = std::exchange(rhs.cleanSocket, INVALID_SOCKET);

		return *this;
	}

    ~CleanSocket() noexcept {
        if (cleanSocket != INVALID_SOCKET) {
            std::ignore = closesocket(cleanSocket);
        }
    }

private:
    SOCKET cleanSocket = { INVALID_SOCKET };
};

std::string sendGetRequestWithSocket(CleanSocket* tcpSocketIPV4, char origin[]);

int main() {
	AmthSocket::SocketImpl sock{};

	CleanSocket tcpSocketIPV4( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	char origin[] = "www.google.com";

	std::cout << sendGetRequestWithSocket(&tcpSocketIPV4,origin) << std::endl;

}

std::string sendGetRequestWithSocket(CleanSocket *tcpSocketIPV4,char origin[]) {
	addrinfo hints{};

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	addrinfo* results{};

	const char* port = "80";

	if (getaddrinfo(origin, "80", &hints, &results) != 0) {
		//TODO: handle error
		//return 1;
	}

	sockaddr_in Address{};
	memcpy_s(&Address, sizeof(Address), results->ai_addr, results->ai_addrlen);


	freeaddrinfo(results);

	connect(tcpSocketIPV4->Get(), reinterpret_cast<const sockaddr*>(&Address), sizeof(Address));

	char request[1024] = "GET / HTTP/1.1\r\n";
	strcat_s(request,origin);
	strcat_s(request, "Connection: close\r\nUser-Agent:TestAgent\r\n\r\n");

	send(tcpSocketIPV4->Get(), request, sizeof(request), 0);

	char buffer[1024]{};
	recv(tcpSocketIPV4->Get(), buffer, sizeof(buffer), 0);

	return buffer;
}

/*
	//SOCKET tcpSocketIPV6 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

	//udp sockets as well for ipv4 and ipv6
	SOCKET udpSocketIPV4 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKET udpSocketIPV6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

*/