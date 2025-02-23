#pragma once

#include <vector>
#include "serversock.h"
#include "ast.h"

class ServerNode : public ASTreeNode
{
public:
	ServerNode(std::string name, std::string attributes, std::string content);
	~ServerNode();

private:


};

ServerNode::ServerNode(std::string name, std::string attributes,std::string content)
{
	std::vector<HTMLTagData> parsed_content = ASTreeNode::parse_html_content(content);
	for (auto& tag_data : parsed_content) {
		//create a function that determines the tag classes
		this->AddChild(new ASTreeNode(tag_data.tag, tag_data.attributes, tag_data.content ));
	}
	
	
}

ServerNode::~ServerNode()
{
}