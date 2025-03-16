#pragma once


#include "ast.h"
#include "ast_manager.h"
#include <iostream>

class APINode : public ASTreeNode
{
public:
	APINode();
	~APINode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content)
	{
		addTagName(name, this);
		setNodeAttributes(ASTManager::parseattributes(attributes), this);
		ASTManager::addNodeChildrenFromContent(content, this);

	}

private:
	friend ASTManager;

};

APINode::APINode()
{

}

APINode::~APINode()
{
}