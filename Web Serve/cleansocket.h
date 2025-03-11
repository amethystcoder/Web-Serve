#pragma once

#include <string>
#include <system_error>
#include <WS2tcpip.h>
#include <iostream>


class CleanSocket {
    public:
        CleanSocket(int address_family = AF_INET, int sockettype = SOCK_STREAM, int protocol = IPPROTO_TCP) {
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

//should be able to handle other forms of connection
/*
    //SOCKET tcpSocketIPV6 = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);

    //udp sockets as well for ipv4 and ipv6
    SOCKET udpSocketIPV4 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    SOCKET udpSocketIPV6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);

*/