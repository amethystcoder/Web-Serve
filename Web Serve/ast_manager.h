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

	static void addNodeChildrenFromContent(const std::string& content, ASTreeNode* node) {
		TagDataList parsed_content = FileParser::parse_html_content(content);
		for (auto& tag_data : parsed_content) {
			//create a function that determines the tag classes

			//IMPORTANT!!!!!!!!
			std::shared_ptr<ASTreeNode> astInstance = ASTNodeFactory::getInstance().create(tag_data.tag);
			if(astInstance != nullptr){
				astInstance->registernode(tag_data.tag, tag_data.attributes, tag_data.content);
				node->AddChild(astInstance);
				//all classes should be derived from ASTreeNode
			}	
		}
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