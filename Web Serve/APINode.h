#pragma once


#include "ast.h"
#include "ast_manager.h"

class APINode : public ASTreeNode
{
public:
	APINode();
	~APINode();

	void registernode(const std::string& name, const std::string& attributes, const std::string& content)
	{
		addTagName(name, *this);
		setNodeAttributes(ASTManager::parseattributes(attributes), this);
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