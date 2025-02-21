#pragma once
#include <vector>



class ASTreeNode
{

	//A tree node for the abstract syntax tree
	//it would contain children and they would also be of type ASTreeNode
	//other classes in the server html tree would be derived from this class
public:
	ASTreeNode();
	~ASTreeNode();

	typedef std::vector<ASTreeNode*> NodeChildren;

	//add a child to the node
	void AddChild(ASTreeNode* child)
	{
		children.push_back(child);
	}


	//remove a child from the node
	//removal should actually never happen except in rare cases
	void RemoveChild(ASTreeNode* child)
	{
		//find the child and remove it
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i] == child)
			{
				children.erase(children.begin() + i);
				break;
			}
		}
	}

	//get the children of the node
	NodeChildren GetChildren ()
	{
		return children;
	}


private:
	//use vector to store children
	NodeChildren children;
};

ASTreeNode::ASTreeNode()
{
}

ASTreeNode::~ASTreeNode()
{
}