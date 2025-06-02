#include "PathResolver.h"


PathResolver::PathResolver()
{
}

PathResolver::~PathResolver()
{
}

// Resolves a relative path based on the main path provided.
//mainPath: The main path to use as a base. i.e., C:\Users\Example\Documents\Project
//PathToResolve: The path to resolve relative to the main path. i.e , ..\Assets\image.png

//note make this function to not throw an exception
std::string PathResolver::resolvePath(const std::string& MainPath, const std::string& PathToResolve)
{
	try
	{
		std::filesystem::path base(MainPath);
		std::filesystem::path resolved = base.parent_path() / PathToResolve;
		return std::filesystem::weakly_canonical(resolved).string();
	}
	catch (const std::exception&)
	{
		return ""; // Return an empty string if the path resolution fails
	}
}
