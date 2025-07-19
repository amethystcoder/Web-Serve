#ifndef ROUTENODE_H
#define ROUTENODE_H

#include "../ast/ast.h"
#include "../util/mimetypes.h"
#include "../process/connectionRequest.h"
#include <filesystem>
#include <iostream>
#include "ServerNode.h"
#include "RatelimitNode.h"

class RouteNode : public ASTreeNode
{
public:
	RouteNode();
	~RouteNode();


	void registernode(const std::string& name, const std::string& attributes, std::string& content);


	inline void setParams() noexcept;

	std::string getFullResponse() noexcept;

	std::string determineResponseStatus() noexcept;

	std::string determineResponse();

	std::string determineContentType() noexcept;

	std::string getEndpoint();

	std::string getMethod();

	std::string getResponse();

	std::string getResContentType();
	std::string setEndpointContent(const std::string& content);

	ProcessEntry* getattachable(NodeDependencies& dependencies) override;
private:
	std::string endpoint;
	std::string rescontenttype;
	std::string method;
	std::string response;

};


#endif // !ROUTENODE_H