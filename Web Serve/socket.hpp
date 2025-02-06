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

#include <iostream>
#include <stdexcept>
#include <WinSock2.h>
#include <system_error>

void handleStartupError(int errorcode) {}


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
			if (startupResult != 0) {
				//do something here
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
			//do something here
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
