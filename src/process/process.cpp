#include "process.h"


//AstreeNode* | a list of the nodes dependencies
ProcessEntry processNodes;


bool CelProcess::attachProcess(ProcessEntry* process) noexcept
{
		processNodes.emplace_back(process);
		return true;
}

//the process: this is a loop that runs the repeatables of each node in the AST
void CelProcess::beginprocess()
{
	while (true)
	{
		for (auto& repeatable : processNodes) {
			//TODO: check the node later for order/priority of execution
			repeatable->process(); //we will set the process to take the dependencies as an argument later
		}
	}
	return;
}
