#pragma once

#ifndef APINODE
#define APINODE

#include "ast.h"
#include "ast_manager.h"
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