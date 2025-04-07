#include "ast_manager.h"
#include <iostream>

ASTManager::ASTManager()
{
}

ASTManager::~ASTManager()
{
}


void ASTManager::addNodeChildrenFromContent(std::string& content, ASTreeNode* node) {
	TagDataList parsed_content = FileParser::parse_html_content(content);
	for (auto& tag_data : parsed_content) {
		//create a function that determines the tag classes

		std::shared_ptr<ASTreeNode> astInstance = ASTNodeFactory::getInstance().create(tag_data.tag);
		if (astInstance != nullptr) {
			ASTreeNode::addTagName(tag_data.tag, astInstance.get());
			ASTreeNode::setNodeAttributes(ASTManager::parseattributes(tag_data.attributes), astInstance.get());
			//use the file parser to change the content based on an attribute called `sref`
			//the sref is given more priority than the content directly placed in the tag
			std::string sref = astInstance->nodeAttributes["sref"];
			if (!sref.empty()) tag_data.content = FileParser::readHtmlFile(sref);
			ASTManager::addNodeChildrenFromContent(tag_data.content, astInstance.get());
			node->AddChild(astInstance);
			//all classes should be derived from ASTreeNode
		}
	}
}

//Find a route node with a specific endpoint
ASTreeNode* ASTManager::findRouteNodeWithEndpoint(const std::string& endpoint, ASTreeNode* startnode) {
	if (!startnode) return nullptr;

	//Check if current node is the matching route node
	if (startnode->getTagName() == "route" && startnode->nodeAttributes["endpoint"] == endpoint) return startnode;

	//Recursively search children
	for (auto& child : startnode->GetChildren()) {
		ASTreeNode* result = findRouteNodeWithEndpoint(endpoint, child.get());
		if (result) return result; 
	}

	return nullptr; //Not found in this branch
}

ASTreeNode* ASTManager::findNodeWithName(const std::string& name, ASTreeNode* startnode) {
	if (!startnode) return nullptr;

	if (startnode->getTagName() == name) return startnode;

	//Recursively search children
	for (auto& child : startnode->GetChildren()) {
		ASTreeNode* result = findNodeWithName(name, child.get());
		if (result) return result;
	}

	return nullptr; //Not found in this branch
}

void ASTManager::setEndpointContent(const std::string& content, ASTreeNode* node){
	//
	std::cout << "content:" << content << std::endl;
	std::string filecontent = content;
	if (FileParser::check_is_html(content)) filecontent = FileParser::readHtmlFile(content);
	
		
	if (node->getTagName() == "route") {
		node->nodeAttributes["response"] = filecontent;
	}
}

std::map<std::string, std::string> ASTManager::parseattributes(const std::string& attributes) {
	return FileParser::parseAttributes(attributes);
}


