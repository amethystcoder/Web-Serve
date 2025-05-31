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
std::string PathResolver::resolvePath(const std::string& MainPath, const std::string& PathToResolve) noexcept {
    std::filesystem::path base(MainPath);
    std::filesystem::path resolved = base.parent_path() / PathToResolve;
    return std::filesystem::weakly_canonical(resolved).string();
}
