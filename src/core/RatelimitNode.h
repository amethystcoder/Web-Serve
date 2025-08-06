#ifndef RATELIMITNODE_H
#define RATELIMITNODE_H

#include <map>
#include <ctime>
#include <chrono>
#include <thread>
#include "../ast/ast.h"
#include "../ast/ast_manager.h"
#include <mutex>


class RateLimitNode : public ASTreeNode
{
public:
	RateLimitNode();
	~RateLimitNode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);

	bool beginLimit();

	void addNewIpaddress(const std::string& ip_address);

	void removeIpaddress(std::string& ip_address);

	//void StartSynchronousLimiting();

	bool isRateLimited(const std::string& ip_address);

	int getIpAttempts(const std::string& ip_address);

	//void startCentralResetThread();

	//void startCentralResetThread();

private:
	std::string time;
	unsigned short int rate;

	std::mutex attempts_mutex;

	//ipaddress => <attempts, last reset time>
	std::map<std::string, std::pair<uint16_t,uint64_t>> ip_attempts_map;

	std::vector<RawDependency*> rawDependencies = {};
};

#endif // !RATELIMITNODE_H