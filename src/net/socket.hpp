//
// Amethystcoder
// Web Server Project
// 
// 2024

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x501
#endif // !_WIN32_WINNT

#ifndef SocketImpl

#define Amthsocket

#define SOCKETCONNECTIONSUCCESS 0

#include <iostream>
#include <stdexcept>
#include <WinSock2.h>
#include <system_error>

#pragma comment(lib, "Ws2_32.lib")


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

		explicit SocketImpl(std::nothrow_t);


		inline bool isInitialized() const noexcept;

		inline const WSADATA& getWSAData() const noexcept;

		void handleStartupError(int errorcode);
	private:
		WSADATA WSAdata{};

		bool socketInitialized = false;
	};
}

#endif // !SocketImpl