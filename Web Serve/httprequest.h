#pragma once

#ifndef CRLF
#define CRLF "\r\n"
#endif // !1

#ifndef DBCRLF
#define DBCRLF "\r\n\r\n"
#endif // !


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

	static HTTPRequestMethods GetRequestType(std::string& headers) noexcept {
		//return the request method based on the enum
		HTTPHeaderMap header_map = ParseRequest(headers);
		std::string request_type = header_map["request_type"];
		if (request_type == "GET ") return GET;
		else if (request_type == "POST ") return POST;
		else if (request_type == "PUT ") return PUT;
		else if (request_type == "DEL ") return DEL;
		else if (request_type == "HEAD ") return HEAD;
		else if (request_type == "OPTIONS ") return OPTIONS;
		else if (request_type == "TRACE ") return TRACE;
		else if (request_type == "CONNECT ") return CONNECT;
		else return GET;
	}

	static std::string GetRequestPath(std::string& headers) noexcept {
		HTTPHeaderMap header_map = ParseRequest(headers);
		return header_map["path"];
	}

	static std::string GetRequestVersion(std::string& headers) noexcept {
		HTTPHeaderMap header_map = ParseRequest(headers);
		return header_map["version"];
	}

	static std::string GetRequestBody(std::string& headers) noexcept {
		std::string header = "", body = "";

		size_t pos = headers.find(DBCRLF);
		if (pos != std::string::npos) {
			header = headers.substr(0, pos);
			body = headers.substr(pos + 4);  // Skip \r\n\r\n
		}
		return body;
	}

	static HTTPHeaderMap ParseRequest(std::string& request) noexcept {
		//headers is a raw http header

		std::string header = "", body = "";

		size_t pos = request.find(DBCRLF);
		if (pos != std::string::npos) {
			header = request.substr(0, pos);
			body = request.substr(pos + 4);  // Skip \r\n\r\n
		}

		//get the first line of the header
		std::string first_line = header.substr(0, header.find_first_of(CRLF));
		//first line is in the format "GET /path/to/resource HTTP/1.1"
		//split the first line into its components
		HTTPHeaderMap header_map;
		header_map["request_type"] = first_line.substr(0, first_line.find_first_of(' ') + 1);
		first_line.erase(0, first_line.find_first_of(' ') + 1);
		header_map["path"] = first_line.substr(0, first_line.find_first_of(' '));
		first_line.erase(0, first_line.find_first_of(' ') + 1);
		header_map["version"] = first_line;
		//erase the first line from the header
		header.erase(0, header.find_first_of(CRLF) + 2);
		//parse the rest of the header
		while (!header.empty())
		{
			std::string key = header.substr(0, header.find_first_of(':'));
			header.erase(0, header.find_first_of(':') + 1);
			header.erase(0, header.find_first_not_of(' '));
			std::string value = header.substr(0, header.find_first_of(CRLF));
			header.erase(0, header.find_first_of(CRLF) + 2);
			header_map[key] = value;
		}
		return header_map;
	}

private:
	HTTPTextParser();
	~HTTPTextParser();
};

HTTPTextParser::HTTPTextParser()
{
}

HTTPTextParser::~HTTPTextParser()
{
}

