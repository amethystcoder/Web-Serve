#pragma once


#include "ast.h"

class APINode : public ASTreeNode
{
public:
	APINode(std::string name, std::string attributes, std::string content);
	~APINode();

private:


};

APINode::APINode(std::string name, std::string attributes, std::string content)
{
	addTagName(name, *this);
	setNodeAttributes(attributes, *this);
	addNodeChildrenFromContent(content, *this);

}

APINode::~APINode()
{
}