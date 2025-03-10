#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>


class ASTreeNode
{

	//A tree node for the abstract syntax tree
	//it would contain children and they would also be of type ASTreeNode
	//other classes in the server html tree would be derived from this class
public:
	ASTreeNode() = default;
	
	~ASTreeNode() = default;

	typedef std::vector<std::shared_ptr<ASTreeNode>> NodeChildren;

	//add a child to the node
	void AddChild(std::shared_ptr<ASTreeNode> child)
	{
		children.push_back(child);
	}

	virtual void registernode(const std::string& name, const std::string& attributes, const std::string& content){}


	//remove a child from the node
	//removal should actually never happen except in rare cases
	void RemoveChild(std::shared_ptr<ASTreeNode> child)
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
	NodeChildren GetChildren ()
	{
		return children;
	}

	//this method can be overloaded if each child has specific unique attributes
	static void setNodeAttributes(const std::string& attributes, ASTreeNode* node) {
		//parse the attributes and set the attributes of the node
		//attributes string looks like class='weird class' or id='weird id'
		//create a map of the attributes
		
	}

	
	void addTagName(const std::string& tagname, ASTreeNode node) {
		//add the tag name to the node
		name = tagname;
	}

private:
	//use vector to store children
	NodeChildren children;

	std::string name;
	std::map<std::string, std::string> nodeAttributes;
};




/*
void addTagClass(std::string tag, ASTreeNode node) {
	std::map<std::string, auto> tagClass;
	tagClass = { {tag, node}, {tag, ServerNode} };
}
*/