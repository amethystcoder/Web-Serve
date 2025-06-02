
#include "cleansocket.h"

CleanSocket::CleanSocket(int address_family, int sockettype, int protocol) {
	cleanSocket = socket(address_family, sockettype, protocol);
	if (cleanSocket == INVALID_SOCKET) {
		throw std::system_error(WSAGetLastError(), std::system_category());
	}
}

SOCKET CleanSocket::Get() const noexcept {
	return cleanSocket;
}

CleanSocket::CleanSocket(CleanSocket&& rhs) noexcept :
	cleanSocket{ std::exchange(rhs.cleanSocket, INVALID_SOCKET) }
{}

CleanSocket& CleanSocket::operator = (CleanSocket&& rhs) noexcept {
	if (cleanSocket != INVALID_SOCKET) {
		std::ignore = closesocket(cleanSocket);
	}

	cleanSocket = std::exchange(rhs.cleanSocket, INVALID_SOCKET);

	return *this;
}

CleanSocket::~CleanSocket() noexcept {
	if (cleanSocket != INVALID_SOCKET) {
		std::ignore = closesocket(cleanSocket);
	}
}

