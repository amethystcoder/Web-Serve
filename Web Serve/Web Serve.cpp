#include "socket.hpp"
#include <system_error>
#include <iostream>
#include "cleansocket.h"
#include "clientsock.h"
#include "serversock.h"
#include "ServerNode.h"
#include <regex>
#include <vector>
#include "ast.h"
#include "fileParser.h"
#include "RouteNode.h"
#include "APINode.h"
#include "ast_factory.h"


static void registerClasses();

int main() {
	//register classes
	registerClasses();

	std::string html_text = "<server port='5000'><api><routes></routes></api><DB class='weird class'/></server><content></content> <DB class='weird class'/>";

	
	std::vector<HTMLTagData> firstNodeList = FileParser::parse_html_content(html_text);
	//create a tree of the html text
    //ensure that the first tag is the root tag and the root tag is <server> 
	//if there are two sibling tags then the first tag is the root tag 
	//as long as there is a server sibling tag, the other tags would be ignored

	ServerNode* serverNode{};
	
	for (auto &tag_data : firstNodeList) {
		//create a node for the root tag
		// search for the server tag
		if (tag_data.tag == "server") {
			//ensure that the root tag is the server tag
			//any tag not under the server tag would be ignored

			//create a node for the server tag
			serverNode = new ServerNode(tag_data.tag, tag_data.attributes,tag_data.content);//, tag_data.content
			//if the server tag is not found then the html text is invalid
			if (serverNode == nullptr) {
				std::cerr << "Invalid html text. The root tag should be <server> tag" << std::endl;
				return 1;
			}
			break;
		}
	}


}

// Helper function to register classes
static void registerClasses() {
	ASTNodeFactory::getInstance().registerClass("server", []() { return std::make_unique<ServerNode>(); });
	ASTNodeFactory::getInstance().registerClass("route", []() { return std::make_unique<RouteNode>(); });
	ASTNodeFactory::getInstance().registerClass("api", []() { return std::make_unique<APINode>(); });
}