#pragma once

#ifndef APINODE
#define APINODE

#include "../ast/ast.h"
#include "../ast/ast_manager.h"
#include <iostream>

class APINode : public ASTreeNode
{
public:
	APINode();
	~APINode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);

private:
	friend ASTManager;

};

#endif // !APINODE