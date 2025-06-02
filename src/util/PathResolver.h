#ifndef PATHRESOLVER_H
#define PATHRESOLVER_H

#include <string>
#include <filesystem>

class PathResolver
{
public:
	PathResolver();
	~PathResolver();

	static std::string resolvePath(const std::string& mainPath, const std::string& PathToResolve) ;

private:

};
#endif // !PATHRESOLVER_H
