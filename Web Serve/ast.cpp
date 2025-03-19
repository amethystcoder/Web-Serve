#include "ast.h"


void ASTreeNode::registernode(const std::string& name, const std::string& attributes, const std::string& content)
{
}

void ASTreeNode::AddChild(std::shared_ptr<ASTreeNode> child)
{
	children.push_back(child);
}


//remove a child from the node
	//removal should actually never happen except in rare cases
void ASTreeNode::RemoveChild(std::shared_ptr<ASTreeNode> child)
{
	//find the child and remove it
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] == child)
		{
			children.erase(children.begin() + i);
			//add code to actually delete child node here
			break;
		}
	}
}

//get the children of the node
ASTreeNode::NodeChildren ASTreeNode::GetChildren()
{
	return children;
}

//this method can be overloaded if each child has specific unique attributes
void ASTreeNode::setNodeAttributes(std::map<std::string, std::string> attributes, ASTreeNode* node) {
	//parse the attributes and set the attributes of the node
	//attributes string looks like class='weird class' or id='weird id'
	//create a map of the attributes
	node->nodeAttributes = attributes;
}


void ASTreeNode::addTagName(const std::string& tagname, ASTreeNode* node) {
	//add the tag name to the node
	node->name = tagname;
}

std::string ASTreeNode::getTagName() const noexcept {
	return name;
}