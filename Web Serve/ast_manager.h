#pragma once
#include "fileParser.h"
#include "ast.h"
#include "ast_factory.h"
#include <unordered_map>

class ASTManager
{
public:
	ASTManager();
	~ASTManager();

	static void addNodeChildrenFromContent(std::string& content, ASTreeNode* node) {
		TagDataList parsed_content = FileParser::parse_html_content(content);
		for (auto& tag_data : parsed_content) {
			//create a function that determines the tag classes

			std::shared_ptr<ASTreeNode> astInstance = ASTNodeFactory::getInstance().create(tag_data.tag);
			if(astInstance != nullptr){
				ASTreeNode::addTagName(tag_data.tag, astInstance.get());
				ASTreeNode::setNodeAttributes(ASTManager::parseattributes(tag_data.attributes), astInstance.get());
				ASTManager::addNodeChildrenFromContent(tag_data.content, astInstance.get());
				node->AddChild(astInstance);
				//all classes should be derived from ASTreeNode
			}
		}
	}

	static ASTreeNode* findRouteNodeWithEndpoint(const std::string& endpoint, ASTreeNode* startnode) {
		if (!startnode) return nullptr;

		//Check if current node is the matching route node
		if (startnode->getTagName() == "route" && startnode->nodeAttributes["endpoint"] == endpoint) return startnode;

		//Recursively search children
		for (auto& child : startnode->GetChildren()) {
			ASTreeNode* result = findRouteNodeWithEndpoint(endpoint, child.get());
			if (result) return result; //Stop as soon as we find a match
		}

		return nullptr; //Not found in this branch
	}

	static std::map<std::string, std::string> parseattributes(const std::string& attributes) {
		return FileParser::parseAttributes(attributes);
	}

private:

};

ASTManager::ASTManager()
{
}

ASTManager::~ASTManager()
{
}
