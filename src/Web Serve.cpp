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

	std::string html_text = "<server port='5000' message='server is running on port {self.port}'>< ratelimit maxRequests = '100' per = '60s' name = 'someratelimitname' message = 'rate limiter is created... or something' / ><filesystem name = 'thefilesys' path = '/' / ><api><route endpoint = '/name' method = 'GET' rescontenttype = 'html' response = 'HTMLPage.html' rateLimit = 'someratelimitname'>< / route><route endpoint = '/stats' method = 'GET' rescontenttype = 'html' response = 'kjfdkj.html'>< / route><route endpoint = '/wonder' method = 'GET' rescontenttype = 'json' response = 'some file.json'>< / route><route endpoint = '/equip' method = 'GET' rescontenttype = 'html' response = 'Hello, You are in the equip page!'>< / route>< / api>< / server> ";

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

