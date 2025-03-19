#include "socket.hpp"

AmthSocket::SocketImpl::SocketImpl()
{
	const int startupResult = WSAStartup(WINSOCK_VERSION, &WSAdata);
	if (startupResult != 0) {
		//Throw an exception
		throw std::system_error(startupResult, std::system_category());
	}

	socketInitialized = true;
}

AmthSocket::SocketImpl::~SocketImpl() noexcept
{
	if (socketInitialized) {
		std::ignore = WSACleanup();
		/* if (cleanupResult != 0) {
			int WSAerror = WSAGetLastError();
		} */
	}
}

void AmthSocket::SocketImpl::handleStartupError(int errorcode) {
	std::cerr << "Error: " << errorcode << std::endl;
	//handle each category of error
	switch (errorcode)
	{
	case WSASYSNOTREADY:
		std::cerr << "The underlying network subsystem is not ready for network communication." << std::endl;
		break;
	case WSAVERNOTSUPPORTED:
		std::cerr << "The version of Windows Sockets support requested is not provided by this particular Windows Sockets implementation." << std::endl;
		break;
	case WSAEINPROGRESS:
		std::cerr << "A blocking Windows Sockets 1.1 operation is in progress." << std::endl;
		break;
	case WSAEPROCLIM:
		std::cerr << "A limit on the number of tasks supported by the Windows Sockets implementation has been reached." << std::endl;
		break;
	case WSAEFAULT:
		std::cerr << "The lpWSAData parameter is not a valid pointer." << std::endl;
		break;
	case WSANOTINITIALISED:
		std::cerr << "A successful WSAStartup call must occur before using this function." << std::endl;
		break;
	default:
		break;
	}
	//still deciding whether it is a good idea to throw an exception here or not
	//throw std::system_error(errorcode, std::system_category());
}


AmthSocket::SocketImpl::SocketImpl(std::nothrow_t) {
	const int startupResult = WSAStartup(WINSOCK_VERSION, &WSAdata);
	if (startupResult != SOCKETCONNECTIONSUCCESS) {
		//TODO: Handle the error here 
		handleStartupError(WSAGetLastError());
		return;
	}

	socketInitialized = true;
}


inline bool AmthSocket::SocketImpl::isInitialized() const noexcept {
	return socketInitialized;
}

inline const WSADATA& AmthSocket::SocketImpl::getWSAData() const noexcept {
	return WSAdata;
}