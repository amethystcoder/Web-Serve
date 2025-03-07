#pragma once

#include "ast.h"
#include "ast_manager.h"

class RouteNode : public ASTreeNode
{
public:
	RouteNode();
	~RouteNode();


	void registernode(std::string name, std::string attributes, std::string content)
	{
		addTagName(name, *this);
		setNodeAttributes(attributes, this);
		ASTManager::addNodeChildrenFromContent(content, this);

	}
private:


};

RouteNode::RouteNode()
{
}

RouteNode::~RouteNode()
{
}