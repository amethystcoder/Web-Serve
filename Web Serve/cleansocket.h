#ifndef CLEANSOCKET_H
#define CLEANSOCKET_H

#include <string>
#include <system_error>
#include <WS2tcpip.h>
#include <iostream>
#include "socket.hpp"


class CleanSocket {
public:
    CleanSocket(int address_family = AF_INET, int sockettype = SOCK_STREAM, int protocol = IPPROTO_TCP);

    SOCKET Get() const noexcept;

    CleanSocket(const CleanSocket&) = delete;
    CleanSocket& operator = (const CleanSocket&) = delete;

    CleanSocket(CleanSocket&& rhs) noexcept;

    CleanSocket& operator = (CleanSocket&& rhs) noexcept;

    ~CleanSocket() noexcept;

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

#endif //CLEANSOCKET_H