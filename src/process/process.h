#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <vector>
#include <set>
#include "../ast/ast.h"
#include "../ast/ast_manager.h"
#include "process/connectionRequest.h"
#include <functional>
#include <memory>


using RepProcess = std::function<void()>; //repeatable process type, a function that takes a list of dependencies and does something with them

//smart pointer containing the repeatable process
using RepProcessPtr = std::shared_ptr<RepProcess>;

struct ProcessEntry {
	ASTreeNode* node;
	ASTreeNode::NodeDependencies deps;
	RepProcess process;

	ProcessEntry(ASTreeNode* n, ASTreeNode::NodeDependencies d, RepProcess p)
		: node(n), deps(std::move(d)), process(std::move(p)) {}
};

struct RawDependency {
	std::string depNodeName; //name of the dependency
	std::string depName;
};

class CelProcess
{
public:

	CelProcess(CelProcess&& other) noexcept = default;
	CelProcess& operator=(CelProcess&& other) noexcept = default;
	//delete copy constructor and assignment operator to enforce singleton
	~CelProcess() = default;

	CelProcess() = default;

	bool attachProcess(ProcessEntry* process);

	void beginprocess();

	static CelProcess& getInstance() noexcept {
		static CelProcess instance;
		return instance;
	}

private:
	//AstreeNode* | a list of the nodes dependencies
	std::vector<ProcessEntry*> processNodes;
	friend ASTManager;
};
#endif // !PROCESS_H
