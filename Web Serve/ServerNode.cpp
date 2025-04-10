#include "ServerNode.h"
#include "RatelimitNode.h"

ServerNode::ServerNode()
{
	this->port = 8080;
	this->cleanSocket = new CleanSocket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

ServerNode::~ServerNode()
{
	delete this->cleanSocket;
}

void ServerNode::registernode(const std::string& name, const std::string& attributes, std::string& content)
{
	addTagName(name, this);
	setNodeAttributes(ASTManager::parseattributes(attributes), this);
	ASTManager::addNodeChildrenFromContent(content, this);

}

//this would or should not throw any execptions 
//it would return false if the port is not a number
bool ServerNode::setPort(const std::string& port) noexcept {
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

void ServerNode::startUpServer() {
	this->setPort(this->nodeAttributes["port"]);
	AmthSocket::ServerSocket server{};
	server.listenforConnections(this->cleanSocket, this->address, this->port);
	while (true) {
		//need to put this in its own thread and function
		SOCKET clientSocket = server.acceptConnection(this->cleanSocket);
		//TODO: note that this only works if it is a get request
		//We need to implement a way to handle other request types
		std::string request_data = server.receiveData(clientSocket);
		HTTPHeaderMap headers = HTTPTextParser::ParseRequest(request_data);
		RouteNode* routeWithEndpoint = reinterpret_cast<RouteNode*>(ASTManager::findRouteNodeWithEndpoint(headers["path"], this));
		//check if the route with the endpoint exists and that the node is a route node
		if (routeWithEndpoint != nullptr && routeWithEndpoint->getTagName() == "route") {
			//check if the route has a rate limit
			if (routeWithEndpoint->nodeAttributes.find("rateLimit") != routeWithEndpoint->nodeAttributes.end()) {
				//get the address of the client and get the ratelimit node based on the name
				RateLimitNode* rateLimitNode = reinterpret_cast<RateLimitNode*>(ASTManager::findNodeWithName(routeWithEndpoint->nodeAttributes["rateLimit"], this));
				//this is just a test and i will remove it later
				//std::string tester = "";
				//rateLimitNode->registernode("","",tester);
				if (rateLimitNode == nullptr) {
					server.sendData(clientSocket, "HTTP/1.1 500 Internal Server Error\nContent-Type: text/html\n\n<html><body><h1>500 Internal Server Error</h1></body></html>");
					continue;
				}
				struct sockaddr_in clientAddress;
				int clientAddressLen = sizeof(clientAddress);
				getpeername(clientSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
				char ip_str[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, &(clientAddress.sin_addr), ip_str, INET_ADDRSTRLEN);
				rateLimitNode->addNewIpaddress(ip_str);

				std::cout << "" << ip_str << "amount of requests now" << rateLimitNode->getIpAttempts(ip_str) << std::endl;

				if (rateLimitNode->isRateLimited(ip_str)) {
					//response to the client if the ip address is in the rate limit
					server.sendData(clientSocket, "HTTP/1.1 429 Too Many Requests\nContent-Type: text/html\n\n<html><body><h1>429 Too Many Requests</h1></body></html>");
					continue;
				}
			}
			ASTManager::setEndpointContent(routeWithEndpoint->nodeAttributes["response"], routeWithEndpoint);
			//Send the response
			server.sendData(clientSocket, routeWithEndpoint->getFullResponse().c_str());
		}
		else server.sendData(clientSocket, "HTTP/1.1 404 Not Found\nContent-Type: text/html\n\n<html><body><h1>404 Not Found</h1></body></html>");//send a 404 response
	}
}