#pragma once

#include <string>

#include <system_error>

class MyClass
{
public:
	MyClass();
	~MyClass();

	HTTPRequestMethods GetRequestType(char *headers[]) const noexcept {
		return GET;
	}

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
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

struct HTTPHeader
{

};