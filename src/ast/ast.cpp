#include "ast.h"

ASTreeNode::ASTreeNode() {}

ASTreeNode::~ASTreeNode() {
	// Destructor to clean up children
	for (auto& child : children) {
		child.reset(); // Reset shared_ptr to release the child node
	}
	children.clear();

}

void ASTreeNode::registernode(const std::string& name, const std::string& attributes, std::string& content)
{
}

void ASTreeNode::AddChild(std::shared_ptr<ASTreeNode> child)
{
	child.get()->parent = this; //set the parent of the child to this node
	children.emplace_back(child);
}

void ASTreeNode::printMessage() {
	std::cout << this->nodeAttributes["message"] << "\n";
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

ASTreeNode* ASTreeNode::getParent() const noexcept
{
	if (this->parent == nullptr) 
		std::cerr << "Error: Parent is null for node with tag: " << this->getTagName() << std::endl;
	return this->parent;
}

ProcessEntry* ASTreeNode::getattachable(NodeDependencies& dependencyList)
{
	RepProcess process = [&dependencyList]() {
		// Default implementation does nothing
	};
	ProcessEntry* newEntry = new ProcessEntry(this, dependencyList, process);
	return newEntry;
}

//TODO: Remember to move this method to a more appropriate place
ASTreeNode* ASTreeNode::getDependency(NodeDependencies& deps, const std::string& name) const noexcept
{
	for (const auto& dep : deps) {
		if (dep->getTagName() == name) {
			return dep.get();
		}
	}
	return nullptr; // Not found
}

std::vector<RawDependency*> ASTreeNode::getRawDependencies() const noexcept {
	return rawDependencies; //whether dependecies are determined or not, this will return the raw dependencies
}

