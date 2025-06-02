#include "ast_manager.h"
#include <iostream>
#include <core/ServerNode.h>

ASTManager::ASTManager()
{
}

ASTManager::~ASTManager()
{
}

std::filesystem::path ASTManager::mainPath;

//build the tree from the first node list
// the first tag must be a server tag
ASTreeNode* ASTManager::buildTree(std::filesystem::path htmlPath) {
	mainPath = htmlPath.parent_path(); //set the main path to the html path
	std::string resolvedPath = std::filesystem::weakly_canonical(htmlPath).string();
	std::vector<HTMLTagData> firstNodeList = FileParser::determineParseType(resolvedPath);
	//create a tree of the html text

	for (auto& tag_data : firstNodeList) {
		//create a node for the root tag
		// search for the server tag
		if (tag_data.tag == "server") {
			//ensure that the root tag is the server tag
			//any tag not under the server tag would be ignored

			//create a node for the server tag
			ServerNode* serverNode = new ServerNode();//, tag_data.content
			if (serverNode == nullptr) {
				std::cerr << "Invalid html text. The root tag should be <server> tag" << std::endl;
				return nullptr;
			}
			serverNode->registernode(tag_data.tag, tag_data.attributes, tag_data.content);
			serverNode->startUpServer();
			return serverNode;
		}
	}
	return nullptr;
}

//this function needs proper error handling as well as fixing
void ASTManager::addNodeChildrenFromContent(std::string& content, ASTreeNode* node) {
	TagDataList parsed_content = FileParser::parse_html_content(content);
	for (auto& tag_data : parsed_content) {
		//create a function that determines the tag classes

		std::shared_ptr<ASTreeNode> astInstance = ASTNodeFactory::getInstance().create(tag_data.tag);
		if (astInstance != nullptr) {
			ASTreeNode::addTagName(tag_data.tag, astInstance.get());
			ASTreeNode::setNodeAttributes(ASTManager::parseattributes(tag_data.attributes), astInstance.get());
			//use the file parser to change the content based on an attribute called `sref`
			//the sref is given more priority than the content directly placed in the tag
			astInstance->registernode(tag_data.tag, tag_data.attributes, tag_data.content);
			std::string sref = astInstance->nodeAttributes["sref"];
			if (!sref.empty()) {
				//TODO there is a small issue here that i need to fix soonest
				std::filesystem::path p(ASTManager::getInstance().getMainPath());
				tag_data.content = FileParser::readHtmlFile(std::filesystem::weakly_canonical(p/sref).string());
			} 
			//ASTManager::addNodeChildrenFromContent(tag_data.content, astInstance.get());
			node->AddChild(astInstance);
			//all classes should be derived from ASTreeNode
		}
	}
}

//Find a route node with a specific endpoint
ASTreeNode* ASTManager::findRouteNodeWithEndpoint(const std::string& endpoint, ASTreeNode* startnode) {
	if (!startnode) return nullptr;

	//Check if current node is the matching route node
	if (startnode->getTagName() == "route" && startnode->nodeAttributes["endpoint"] == endpoint) return startnode;

	//Recursively search children
	for (auto& child : startnode->GetChildren()) {
		ASTreeNode* result = findRouteNodeWithEndpoint(endpoint, child.get());
		if (result) return result; 
	}

	return nullptr; //Not found in this branch
}

ASTreeNode* ASTManager::findNodeWithName(const std::string& name, ASTreeNode* startnode) {
	if (!startnode) return nullptr;

	//work on this tomorrow 

	if (startnode->nodeAttributes.find("name") != startnode->nodeAttributes.end()) {
		if (startnode->nodeAttributes["name"] == name) return startnode;
	}

	//Recursively search children
	for (auto& child : startnode->GetChildren()) {
		ASTreeNode* result = findNodeWithName(name, child.get());
		if (result) return result;
	}

	return nullptr; //Not found in this branch
}

ASTreeNode* ASTManager::findNodeWithTagName(const std::string& Tagname, ASTreeNode* startnode) {
	if (!startnode) return nullptr;

	if (startnode->getTagName() == Tagname) return startnode;

	//Recursively search children
	for (auto& child : startnode->GetChildren()) {
		ASTreeNode* result = findNodeWithTagName(Tagname, child.get());
		if (result) return result;
	}

	return nullptr; //Not found in this branch
}

std::map<std::string, std::string> ASTManager::parseattributes(const std::string& attributes) {
	return FileParser::parseAttributes(attributes);
}

std::filesystem::path ASTManager::getMainPath() const noexcept {
	return mainPath;
}

void ASTManager::setMainPath(std::string& path) noexcept {
	//parse path and remove text behind slashes that might contain an extension
	std::filesystem::path p(path);
	if (p.has_extension()) {
		p = p.parent_path();
	}
	mainPath = p.string();
}