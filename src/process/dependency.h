#ifndef DEPENDENCY_H
#define DEPENDENCY_H


#include <functional>
#include <memory>
#include <string>
#include <vector>



using RepProcess = std::function<void()>; //repeatable process type, a function that takes a list of dependencies and does something with them

struct RawDependency {
	std::string depNodeName; //name of the dependency
	std::string depName;
};

//smart pointer containing the repeatable process
using RepProcessPtr = std::shared_ptr<RepProcess>;


#endif // !DEPENDENCY_H
