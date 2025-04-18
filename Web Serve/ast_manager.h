#ifndef AST_MANAGER_H
#define AST_MANAGER_H

#include "fileParser.h"
#include "ast.h"
#include "ast_factory.h"
#include <unordered_map>

class ASTManager
{
public:
	ASTManager();
	~ASTManager();

	static void addNodeChildrenFromContent(std::string& content, ASTreeNode* node);

	static ASTreeNode* findNodeWithTagName(const std::string& name, ASTreeNode* startnode);

	static ASTreeNode* findRouteNodeWithEndpoint(const std::string& endpoint, ASTreeNode* startnode);

	static void setEndpointContent(const std::string& content,ASTreeNode* node);

	static std::map<std::string, std::string> parseattributes(const std::string& attributes);

	static ASTreeNode* findNodeWithName(const std::string& name, ASTreeNode* startnode);

private:

};

#endif // !AST_MANAGER_H