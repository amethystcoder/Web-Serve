#include "APINode.h"

APINode::APINode()
{
}

APINode::~APINode()
{
}

void APINode::registernode(const std::string& name, const std::string& attributes, std::string& content)
{
	addTagName(name, this);
	setNodeAttributes(ASTManager::parseattributes(attributes), this);
	ASTManager::addNodeChildrenFromContent(content, this);

}