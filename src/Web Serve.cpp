#include <iostream>
#include "net/cleansocket.h"
#include "core/ServerNode.h"
#include "core/databaseNode.h"
#include <vector>
#include "util/fileParser.h"
#include "core/RouteNode.h"
#include "core/APINode.h"
#include "core/RatelimitNode.h"
#include "core/FileSystem.h"
#include "ast/ast_factory.h"


// Helper function to register classes
static void registerClasses() {
	ASTNodeFactory::getInstance().registerClass("server", []() { return std::make_shared<ServerNode>(); });
	ASTNodeFactory::getInstance().registerClass("route", []() { return std::make_shared<RouteNode>(); });
	ASTNodeFactory::getInstance().registerClass("api", []() { return std::make_shared<APINode>(); });
	ASTNodeFactory::getInstance().registerClass("database", []() { return std::make_shared<DatabaseNode>(); });
	ASTNodeFactory::getInstance().registerClass("ratelimit", []() { return std::make_shared<RateLimitNode>(); });
	ASTNodeFactory::getInstance().registerClass("filesystem", []() { return std::make_shared<FileSystem>(); });
}

int main(int argc, char** argv) {

	AmthSocket::SocketImpl sockimpl{};
	registerClasses();

	std::string html_text = "./resources/serverFile.html";

	std::vector<HTMLTagData> firstNodeList = FileParser::determineParseType(html_text);
	//create a tree of the html text

	ServerNode* serverNode{};

	for (auto& tag_data : firstNodeList) {
		//create a node for the root tag
		// search for the server tag
		if (tag_data.tag == "server") {
			//ensure that the root tag is the server tag
			//any tag not under the server tag would be ignored

			//create a node for the server tag
			serverNode = new ServerNode();//, tag_data.content
			if (serverNode == nullptr) {
				std::cerr << "Invalid html text. The root tag should be <server> tag" << std::endl;
				return 1;
			}
			serverNode->registernode(tag_data.tag, tag_data.attributes, tag_data.content);
			serverNode->startUpServer();
			break;
		}
	}
	std::cout << "Server started successfully." << std::endl;
}

