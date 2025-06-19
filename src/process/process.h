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


using dependencies = std::vector<std::shared_ptr<ASTreeNode>>;
using RepProcess = std::function<void(ConnectionRequest,dependencies)>;

//smart pointer containing the repeatable process
using RepProcessPtr = std::shared_ptr<RepProcess>;

class CelProcess
{
public:
	CelProcess();
	~CelProcess();

	CelProcess(CelProcess&& other) noexcept
		: processNodes(std::move(other.processNodes))
	{
		other.processNodes.clear();
	}

	CelProcess& operator=(CelProcess&& other) noexcept
	{
		if (this != &other) {
			processNodes = std::move(other.processNodes);
			other.processNodes.clear();
		}
		return *this;
	}

	bool attachProcess(RepProcessPtr process);

	void beginprocess();

private:
	std::vector<RepProcessPtr> processNodes;
	friend ASTManager;
};
#endif // !PROCESS_H
