#pragma once
#include <vector>
#include <map>
#include "serverNode.h"


struct HTMLTagData {
	std::string tag;
	std::string attributes;
	std::string content;
};

class ASTreeNode
{

	//A tree node for the abstract syntax tree
	//it would contain children and they would also be of type ASTreeNode
	//other classes in the server html tree would be derived from this class
public:
	ASTreeNode(std::string name, std::string atributes, std::string content);
	ASTreeNode() = default;
	
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

	static std::vector<HTMLTagData> parse_html_content(std::string html_text)
	{
		//master tags are the tags that are not nested or are the root tags in a string
		//for example in the html text <server><api></api></server> server is a master tag
		//child tags are not accessed
		std::vector<HTMLTagData> master_tags;
		//regex to parse html text
		std::regex html_regex(R"(<([^<>/\s]+)([^<>]*)>(.*?)<\/\1>|<([^<>/\s]+)([^<>]*)\/>)");
		std::smatch match;

		std::string temp = html_text;

		//parse the html text
		//std::string::const_iterator searchStart(html_text.cbegin());
		while (std::regex_search(temp, match, html_regex))
		{
			if (match[1].matched) {
				// Opening and closing tag like <html> </html>
				std::string tag = match[1];
				std::string attributes = match[2];
				std::string content = match[3];
				HTMLTagData tag_data;
				tag_data.tag = tag;
				tag_data.attributes = attributes;
				tag_data.content = content;
				master_tags.push_back(tag_data);
			}
			else {
				// Self closing tag like <br/>
				std::string tag = match[4];
				std::string attributes = match[5];
				HTMLTagData tag_data;
				tag_data.tag = tag;
				tag_data.attributes = attributes;
				tag_data.content = "";
				master_tags.push_back(tag_data);
			}
			temp = match.suffix().str();
		}

		return master_tags;
	}


private:
	//use vector to store children
	NodeChildren children;
};

ASTreeNode::ASTreeNode(std::string name, std::string atributes,std::string content)
{
}

ASTreeNode::~ASTreeNode()
{
}


/*
void addTagClass(std::string tag, ASTreeNode node) {
	std::map<std::string, auto> tagClass;
	tagClass = { {tag, node}, {tag, ServerNode} };
}
*/
