#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../ast/ast.h"
#include "../ast/ast_manager.h"

class FileSystem: public ASTreeNode
{
public:
	FileSystem();
	~FileSystem();

private:
	std::vector<RawDependency*> rawDependencies = {};
};

#endif // !FILESYSTEM_H