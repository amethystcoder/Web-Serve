#pragma once

#include <vector>
#include "serversock.h"
#include "ast.h"
#include "ast_manager.h"
#include <iostream>

//#include "cleansocket.h"
//#include "socket.hpp"

class ServerNode : public ASTreeNode
{
public:
	ServerNode();
	~ServerNode();

	void registernode(const std::string& name, const std::string& attributes, const std::string& content)
	{
		std::cout << "tag name: " << name << std::endl;
		std::cout << "content: " << content << std::endl;
		std::cout << "attributes: " << attributes << std::endl;

		addTagName(name, *this);
		setNodeAttributes(ASTManager::parseattributes(attributes), this);
		ASTManager::addNodeChildrenFromContent(content, this);

	}

	//this would or should not throw any execptions 
	//it would return false if the port is not a number
	bool setPort(const std::string& port) noexcept {
		//check that the string port actually has numbers in it
		if (port.find_first_not_of("0123456789") != std::string::npos) {
			return false;
		}
		if (std::stoi(port) < 0 || std::stoi(port) > 65535) {
			return false;
		}
		this->port = std::stoi(port);
		return true;
	}

	void startUpServer() {
		this->setPort(this->nodeAttributes["port"]);
		AmthSocket::ServerSocket server{};
		server.listenforConnections(this->cleanSocket, this->address, this->port);
		SOCKET clientSocket = server.acceptConnection(this->cleanSocket);
		server.sendData(clientSocket, "Hello from server");
	}

	friend ASTManager;
private:
	//remember that we are going to abstract the socket class to a higher level
	//so that we can use the socket class in the server class
	//without it having to know the details of the socket class and so it doesn't throw exceptions again
	CleanSocket* cleanSocket;
	AmthSocket::SocketImpl* socket;
	
	unsigned int port = 8080;
	const char* address = "127.0.0.1";
};

ServerNode::ServerNode()
{
	this->port = 8080;
	this->socket = new AmthSocket::SocketImpl();
	this->cleanSocket = new CleanSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ServerNode::~ServerNode()
{
}