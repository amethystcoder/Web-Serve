#pragma once
#include <string>
#include <system_error>
#include <ws2def.h>
#include "cleansocket.h"

namespace AmthSocket
{
	class ServerSocket
	{
		public:
			ServerSocket();
			~ServerSocket() noexcept;

			ServerSocket(const ServerSocket&) = delete;
			ServerSocket& operator = (const ServerSocket&) = delete;

			ServerSocket(ServerSocket&&) noexcept = default;
			ServerSocket& operator = (ServerSocket&&) noexcept = default;



	private:
	};
}