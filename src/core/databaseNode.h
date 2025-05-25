#ifndef DATABASENODE_H
#define DATABASENODE_H

#include "../ast/ast.h"
#include "../ast/ast_manager.h"

class DatabaseNode:public ASTreeNode{
public:
	DatabaseNode();
	~DatabaseNode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);
private:

};

#endif // !DATABASENODE_H