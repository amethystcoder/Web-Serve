#pragma once

#include "ast.h"
#include "ast_manager.h"
#include <iostream>

class RouteNode : public ASTreeNode
{
public:
	RouteNode();
	~RouteNode();


	void registernode(const std::string& name, const std::string& attributes, std::string& content)
	{
		addTagName(name, this);
		setNodeAttributes(ASTManager::parseattributes(attributes), this);
		ASTManager::addNodeChildrenFromContent(content, this);
		setParams();
	}

	//set the string that would be sent as a server response
	//std::string setResponseString() {
		//return this->
	//}

	void setParams() noexcept {
		this->endpoint = endpoint = this->nodeAttributes["endpoint"];
		this->rescontenttype = this->nodeAttributes["rescontenttype"];
		this->method = this->nodeAttributes["method"];
		this->response = this->nodeAttributes["response"];
	}
	std::string getEndpoint() {
		return this->endpoint;
	}

	std::string getMethod() {
		return this->method;
	}

	std::string getResponse() {
		return this->response;
	}

	std::string getResContentType() {
		return this->rescontenttype;
	}
private:
	std::string endpoint;
	std::string rescontenttype;
	std::string method;
	std::string response;

};

RouteNode::RouteNode()
{
}

RouteNode::~RouteNode()
{
}