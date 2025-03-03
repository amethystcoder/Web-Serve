#pragma once
#include <vector>
#include <map>
#include <memory>
#include "fileParser.h"


class ASTreeNode
{

	//A tree node for the abstract syntax tree
	//it would contain children and they would also be of type ASTreeNode
	//other classes in the server html tree would be derived from this class
public:
	ASTreeNode(std::string name, std::string atributes, std::string content);
	ASTreeNode() = default;
	
	~ASTreeNode() = default;

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
	static void setNodeAttributes(std::string attributes) {
		//parse the attributes and set the attributes of the node
		//attributes string looks like class='weird class' or id='weird id'
		//create a map of the attributes
		
	}

	
	void addTagName(std::string tagname, ASTreeNode node) {
		//add the tag name to the node
		name = tagname;
	}

	void addNodeChildrenFromContent(std::string content, ASTreeNode& node) {
		TagDataList parsed_content = FileParser::parse_html_content(content);
		for (auto& tag_data : parsed_content) {
			//create a function that determines the tag classes
			
			this->AddChild(&node);//TODO: write function to determing the class of the tag
			//all classes should be derived from ASTreeNode
		}
	}

private:
	//use vector to store children
	NodeChildren children;

	std::string name;
};

ASTreeNode::ASTreeNode(std::string name, std::string atributes,std::string content)
{
}



/*
void addTagClass(std::string tag, ASTreeNode node) {
	std::map<std::string, auto> tagClass;
	tagClass = { {tag, node}, {tag, ServerNode} };
}
*/