#pragma once

#include "ast.h"

class RouteNode : public ASTreeNode
{
public:
	RouteNode(std::string name, std::string attributes, std::string content);
	~RouteNode();

private:


};

RouteNode::RouteNode(std::string name, std::string attributes, std::string content)
{
	addTagName(name, *this);
	setNodeAttributes(attributes, *this);
	addNodeChildrenFromContent(content, *this);


}

RouteNode::~RouteNode()
{
}