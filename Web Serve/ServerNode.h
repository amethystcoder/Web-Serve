#pragma once

#include <vector>
#include "serversock.h"
#include "ast.h"
#include "ast_manager.h"
#include <iostream>

class ServerNode : public ASTreeNode
{
public:
	ServerNode();
	~ServerNode();

	void registernode(std::string name, std::string attributes, std::string content)
	{
		std::cout << "tag name: " << name << std::endl;
		std::cout << "content: " << content << std::endl;
		std::cout << "attributes: " << attributes << std::endl;

		addTagName(name, *this);
		setNodeAttributes(attributes, this);
		ASTManager::addNodeChildrenFromContent(content, this);

	}

	void startUpServer() {}
private:

	unsigned int port;
};

ServerNode::ServerNode()
{
}

ServerNode::~ServerNode()
{
}