#ifndef AST_H
#define AST_H

#include <vector>
#include <map>
#include <memory>
#include <string>

class ASTreeNode
{

	//A tree node for the abstract syntax tree
	//it would contain children and they would also be of type ASTreeNode
	//other classes in the server html tree would be derived from this class
public:
	ASTreeNode() = default;

	~ASTreeNode() = default;

	typedef std::vector<std::shared_ptr<ASTreeNode>> NodeChildren;

	//add a child to the node
	void AddChild(std::shared_ptr<ASTreeNode> child);

	virtual void registernode(const std::string& name, const std::string& attributes, std::string& content);

	void RemoveChild(std::shared_ptr<ASTreeNode> child);

	NodeChildren GetChildren();

	static void setNodeAttributes(std::map<std::string, std::string> attributes, ASTreeNode* node);


	static void addTagName(const std::string& tagname, ASTreeNode* node);

	std::string getTagName() const noexcept;

	std::map<std::string, std::string> nodeAttributes;

private:
	//use vector to store children
	NodeChildren children;

	std::string name;
};


#endif // !AST_H

