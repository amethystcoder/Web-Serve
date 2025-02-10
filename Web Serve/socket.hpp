//
// Amethystcoder
// Web Server Project
// 
// 2024

#ifndef Amthsocket

#define Amthsocket

#endif // !components

#ifndef _WIN32_WINNT 

#define _WIN32_WINNT 0x501

#endif // !

#ifndef SOCKETCONNECTIONSUCCESS

#define SOCKETCONNECTIONSUCCESS 0

#endif // !SOCKETCONNECTIONSUCCESS

#include <iostream>
#include <stdexcept>
#include <WinSock2.h>
#include <system_error>

void handleStartupError(int errorcode) {
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


namespace AmthSocket {


	class SocketImpl
	{
	public:
		SocketImpl();
		~SocketImpl() noexcept;

		SocketImpl(const SocketImpl&) = delete;
		SocketImpl& operator = (const SocketImpl&) = delete;

		SocketImpl(SocketImpl&& socklib) noexcept :
			socketInitialized{ std::exchange(socklib.socketInitialized,false)},
			WSAdata{ socklib.WSAdata }
		{}


		SocketImpl& operator = (SocketImpl&& rhs) noexcept {
			socketInitialized = std::exchange(rhs.socketInitialized, false);
			WSAdata = rhs.WSAdata ;

			return *this;
		}

		explicit SocketImpl(std::nothrow_t) {
			const int startupResult = WSAStartup(WINSOCK_VERSION, &WSAdata);
			if (startupResult != SOCKETCONNECTIONSUCCESS) {
				//TODO: Handle the error here gracefully
				handleStartupError(startupResult);
				return;
			}

			socketInitialized = true;
		}


		inline bool isInitialized() const noexcept {
			return socketInitialized;
		}

		inline const WSADATA& getWSAData() const noexcept {
			return WSAdata;
		}
	private:
		WSADATA WSAdata{};

		bool socketInitialized = false;
	};

	SocketImpl::SocketImpl()
	{
		const int startupResult = WSAStartup(WINSOCK_VERSION, &WSAdata);
		if (startupResult != 0) {
			//Throw an exception
			throw std::system_error(startupResult, std::system_category());
		}
		
		socketInitialized = true;
	}

	SocketImpl::~SocketImpl() noexcept
	{
		if (socketInitialized) {
			std::ignore = WSACleanup();
			/* if (cleanupResult != 0) {
				int WSAerror = WSAGetLastError();
			} */
		}
	}
}
