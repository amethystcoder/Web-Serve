#ifndef RATELIMITNODE_H
#define RATELIMITNODE_H

#include <map>
#include <ctime>
#include <chrono>
#include <thread>
#include "ast.h"


class RateLimitNode : public ASTreeNode
{
public:
	RateLimitNode();
	~RateLimitNode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);

	bool startCheck();

	bool beginLimit();

	void addNewIpaddress(const std::string& ip_address);

	void removeIpaddress(std::string& ip_address);

	bool isRateLimited(const std::string& ip_address);

	int getIpAttempts(const std::string& ip_address);

private:
	std::string time;
	short unsigned int rate;

	std::map<std::string, short unsigned int> ip_attempts_map;
};

#endif // !RATELIMITNODE_H

