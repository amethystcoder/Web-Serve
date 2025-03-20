#include "RouteNode.h"


RouteNode::RouteNode()
{
}


RouteNode::~RouteNode()
{
}

void RouteNode::registernode(const std::string& name, const std::string& attributes, std::string& content)
{
	addTagName(name, this);
	setNodeAttributes(ASTManager::parseattributes(attributes), this);
	ASTManager::addNodeChildrenFromContent(content, this);
	setParams();
}

inline void RouteNode::setParams() noexcept {
	std::cout << "Setting params" << std::endl;
	this->endpoint = endpoint = this->nodeAttributes["endpoint"];
	this->rescontenttype = this->nodeAttributes["rescontenttype"];
	this->method = this->nodeAttributes["method"];
	this->response = this->nodeAttributes["response"];
}

std::string RouteNode::getFullResponse() noexcept {
	return this->determineResponseStatus() + this->determineContentType() + this->determineResponse();
}

std::string RouteNode::determineResponseStatus() noexcept {
	this->method = this->nodeAttributes["method"];
	if (this->method == "GET") return "HTTP/1.1 200 OK\n";
	else if (this->method == "POST") return "HTTP/1.1 201 Created\n";
	else if (this->method == "PUT") return "HTTP/1.1 204 No Content\n";
	else if (this->method == "DELETE") return "HTTP/1.1 204 No Content\n";
	else return "HTTP/1.1 200 OK\n";
}

std::string RouteNode::determineResponse() {
	return this->nodeAttributes["response"];
}

std::string RouteNode::determineContentType() noexcept {
	this->rescontenttype = this->nodeAttributes["rescontenttype"];
	if (this->rescontenttype == "json") return "Content-Type: application/json\n\n";
	else if (this->rescontenttype == "html") return "Content-Type: text/html\n\n";
	else if (this->rescontenttype == "xml") return "Content-Type: text/xml\n\n";
	else if (this->rescontenttype == "plain") return "Content-Type: text/plain\n\n";
	else return "Content-Type: text/html\n\n";
}

std::string RouteNode::getEndpoint() {
	return this->endpoint;
}

std::string RouteNode::getMethod() {
	return this->method;
}

std::string RouteNode::getResponse() {
	return this->response;
}

std::string RouteNode::getResContentType() {
	return this->rescontenttype;
}