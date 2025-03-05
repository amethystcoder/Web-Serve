#pragma once

#include <vector>
#include "serversock.h"
#include "ast.h"
#include "ast_manager.h"

class ServerNode : public ASTreeNode
{
public:
	ServerNode(std::string name, std::string attributes, std::string content);
	~ServerNode();

	void startUpServer() {}
private:

	unsigned int port;
};

ServerNode::ServerNode(std::string name, std::string attributes,std::string content)
{
	addTagName(name, *this);
	setNodeAttributes(attributes,this);
	ASTManager::addNodeChildrenFromContent(content, this);
}

ServerNode::~ServerNode()
{
}