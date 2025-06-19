#include "process.h"

std::vector<ASTreeNode*> processNodes;

CelProcess::CelProcess()
{
}

CelProcess::~CelProcess()
{
}

bool CelProcess::attachProcess(RepProcessPtr process) noexcept
{
	if (process) {
		processNodes.emplace_back(process);
		return true;
	}
	return false;
}

//the process: this is a loop that runs the repeatables of each node in the AST
void CelProcess::beginprocess()
{
	while (true)
	{
		for (auto& repeatable : processNodes) {
			//repeatable(nullptr);//we need to attach the dependencies here
		}
	}
	return;
}
