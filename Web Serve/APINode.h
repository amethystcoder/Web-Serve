#pragma once


#include "ast.h"
#include "ast_manager.h"

class APINode : public ASTreeNode
{
public:
	APINode();
	~APINode();

	void registernode(std::string name, std::string attributes, std::string content)
	{
		addTagName(name, *this);
		setNodeAttributes(attributes, this);
		ASTManager::addNodeChildrenFromContent(content, this);

	}

private:


};

APINode::APINode()
{

}

APINode::~APINode()
{
}