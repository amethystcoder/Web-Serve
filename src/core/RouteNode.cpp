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
	this->endpoint = endpoint = this->nodeAttributes["endpoint"];
	this->rescontenttype = this->nodeAttributes["rescontenttype"];
	this->method = this->nodeAttributes["method"];
	this->response = this->setEndpointContent(this->nodeAttributes["response"]);
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
	//check that response is not an html file
	return this->response;
}

std::string RouteNode::determineContentType() noexcept {
	this->rescontenttype = this->nodeAttributes["rescontenttype"];
	return "Content-Type: " + MimeTypes::getInstance().getMimeType(this->rescontenttype);
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

std::string RouteNode::setEndpointContent(const std::string& content) {
	std::string filecontent = content;
	bool isFile = FileParser::check_is_file(content);
	if (isFile) {
		std::filesystem::path responseFilePath = ASTManager::getInstance().getMainPath() / content;
		std::filesystem::path responsePath = std::filesystem::weakly_canonical(responseFilePath);
		this->nodeAttributes["response"] = responsePath.string();
		filecontent = FileParser::readFile(content);
		if (!std::filesystem::exists(responsePath)) {
			std::cout << "File not found: " << responsePath.string() << std::endl;
			filecontent = "<html><body><h1>404 Not Found</h1></body></html>";
		}
	}
	return filecontent;
}