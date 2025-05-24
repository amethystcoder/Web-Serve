#ifndef SERVERNODE_H
#define SERVERNODE_H

#include <vector>
#include "serversock.h"
#include "ast.h"
#include "ast_manager.h"
#include <iostream>
#include "httprequest.h"
#include "RouteNode.h"
#include "cleansocket.h"
#include <winsock.h>

class ServerNode : public ASTreeNode
{
public:
	ServerNode();
	~ServerNode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);

	//this would or should not throw any execptions
	//it would return false if the port is not a number
	bool setPort(const std::string& port) noexcept;

	void startUpServer();
	//friend ASTManager;

	friend ASTManager;
private:
	//remember that we are going to abstract the socket class to a higher level
	//so that we can use the socket class in the server class
	//without it having to know the details of the socket class and so it doesn't throw exceptions again
	CleanSocket* cleanSocket;

	unsigned int port = 8080;
	const char* address = "127.0.0.1";
};



#endif // !SERVERNODE_H