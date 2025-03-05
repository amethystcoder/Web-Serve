#pragma once


#include "ast.h"
#include "ast_manager.h"

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
	setNodeAttributes(attributes,this);
	ASTManager::addNodeChildrenFromContent(content, this);

}

APINode::~APINode()
{
}