#ifndef STORE_H
#define STORE_H

#include "ast/ast.h"

class StoreNode : public ASTreeNode {

public:
	StoreNode();
	~StoreNode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);

	ProcessEntry* getattachable(NodeDependencies& dependencies) override;

private:
	std::vector<RawDependency*> rawDependencies = {};
};
#endif // !STORE_H
