#ifndef AST_H
#define AST_H

#include <vector>
#include <map>
#include <memory>
#include <string>
#include <iostream>
#include <functional>
#include "process/dependency.h"

class ASTreeNode
{

	//A tree node for the abstract syntax tree
	// It is more a server node tree, than an AST, but still works in this case 
	//it would contain children and they would also be of type ASTreeNode
	//other classes in the server html tree would be derived from this class
public:
	ASTreeNode() = default;

	~ASTreeNode() = default;

	typedef std::vector<std::shared_ptr<ASTreeNode>> NodeChildren;
	typedef NodeChildren NodeDependencies;

	//add a child to the node
	void AddChild(std::shared_ptr<ASTreeNode> child);

	virtual void registernode(const std::string& name, const std::string& attributes, std::string& content);

	void RemoveChild(std::shared_ptr<ASTreeNode> child);

	NodeChildren GetChildren();

	static void setNodeAttributes(std::map<std::string, std::string> attributes, ASTreeNode* node);


	static void addTagName(const std::string& tagname, ASTreeNode* node);

	void printMessage();

	std::string getTagName() const noexcept;

	std::map<std::string, std::string> nodeAttributes;

	ASTreeNode* getParent() const noexcept;

	ASTreeNode* getDependency(NodeDependencies& deps, const std::string& name) const noexcept;

	//attachable is a function that is called during the processs
	//a process is a loop that runs during the lifetime of the application
	//the loop checks all the nodes for their 'attachables' and runs each of them
	virtual ProcessEntry* getattachable(NodeDependencies& dependencyList);

	virtual std::vector<RawDependency*> getRawDependencies() const noexcept;
private:

	//use vector to store children
	NodeChildren children;

	//use a vector to store raw dependencies
	std::vector<RawDependency*> rawDependencies;

	//use a vector to store dependencies
	NodeDependencies dependencies; //TODO: make this a set to avoid duplicates, or a priority queue to order them by priority

	bool determinedDependencies = false; //if the dependencies are determined or not

	//use a pointer to the parent node
	ASTreeNode* parent = nullptr;

	std::string name;
};


struct ProcessEntry {
	ASTreeNode* node;
	ASTreeNode::NodeDependencies deps;
	RepProcess process;

	ProcessEntry(ASTreeNode* n, ASTreeNode::NodeDependencies d, RepProcess p)
		: node(n), deps(std::move(d)), process(std::move(p)) {}
};

#endif // !AST_H

