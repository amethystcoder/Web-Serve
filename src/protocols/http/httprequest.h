#ifndef HTTPREQUEST_H

#define HTTPREQUEST_H

#define CRLF "\r\n"
#define DBCRLF "\r\n\r\n"

#include <string>
#include <unordered_map>
#include <system_error>

typedef std::unordered_map<std::string, std::string> HTTPHeaderMap;

enum HTTPRequestMethods
{
	GET,
	POST,
	PUT,
	DEL,
	HEAD,
	OPTIONS,
	TRACE,
	CONNECT
};

typedef struct HTTPHeader
{
	std::string key;
	std::string value;
} HTTPHeader;

//contains utility functions for parsing the raw http request from sockets
class HTTPTextParser
{
public:

	static HTTPRequestMethods GetRequestType(std::string& headers) noexcept;

	static std::string GetRequestPath(std::string& headers) noexcept;

	static std::string GetRequestVersion(std::string& headers) noexcept;

	static std::string GetRequestBody(std::string& headers) noexcept;

	static HTTPHeaderMap ParseRequest(std::string& request) noexcept;

private:
	HTTPTextParser();
	~HTTPTextParser();
};

#endif // HTTPREQUEST_H


