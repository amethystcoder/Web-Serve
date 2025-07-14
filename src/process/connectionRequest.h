#ifndef CONNECTIONREQUEST_H
#define CONNECTIONREQUEST_H

#include "net/serversock.h"
#include "protocols/http/httprequest.h"
#include <mutex>

class ConnectionRequest
{
public:
    //delete copy constructor and assignment operator to enforce singleton
    ConnectionRequest(const ConnectionRequest&) = delete;
    ConnectionRequest& operator=(const ConnectionRequest&) = delete;

    //access the single instance
	static ConnectionRequest& getInstance() noexcept
    {
        static ConnectionRequest instance;
        return instance;
    }

    //thread-safe setters
    void setSocket(SOCKET sock) noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        this->socket = sock;
    }

    void setHeaders(const HTTPHeaderMap& headers) noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        this->headers = headers;
    }

    void setContent(const std::string& content) noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        this->content = content;
    }

    void setIpAddress() noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        this->ipAddress = serverSock.getClientIp(socket);
    }

    //thread-safe getters
    SOCKET getSocket() const noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        return this->socket;
    }

    HTTPHeaderMap getHeaders() const noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        return this->headers;
    }

    std::string getContent() const noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        return this->content;
    }

    std::string getIpAddress() const noexcept {
        std::lock_guard<std::mutex> lock(mutex);
        return this->ipAddress;
    }

private:
    ConnectionRequest() = default;
    ~ConnectionRequest() = default;

    mutable std::mutex mutex;

    std::string ipAddress;
    SOCKET socket;
    HTTPHeaderMap headers;
    AmthSocket::ServerSocket serverSock{};
    std::string content;
};

#endif // !CONNECTIONREQUEST_H
