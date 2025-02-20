#pragma once

#include <string>

#include <system_error>

//contains utility functions for parsing the raw http request from sockets
class HTTPTextParser
{
public:
	HTTPTextParser();
	~HTTPTextParser();

	HTTPRequestMethods GetRequestType(char *headers[]) const noexcept {
		return GET;
	}

private:

};

HTTPTextParser::HTTPTextParser()
{
}

HTTPTextParser::~HTTPTextParser()
{
}


enum HTTPRequestMethods
{
	GET,
	POST,
	PUT,
	DELETE,
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