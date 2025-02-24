#pragma once

#include <vector>
#include "serversock.h"
#include "ast.h"

class ServerNode : public ASTreeNode
{
public:
	ServerNode(std::string name, std::string attributes, std::string content);
	~ServerNode();

private:


};

ServerNode::ServerNode(std::string name, std::string attributes,std::string content)
{
	addTagName(name, *this);
	setNodeAttributes(attributes, *this);
	addNodeChildrenFromContent(content, *this);
	
	
}

ServerNode::~ServerNode()
{
}