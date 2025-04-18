#include "RatelimitNode.h"
#include <iostream>

using namespace std::literals::chrono_literals;

RateLimitNode::RateLimitNode()
{
	this->time = "";
	this->rate = 0;
}

RateLimitNode::~RateLimitNode()
{
}

void RateLimitNode::registernode(const std::string& name, const std::string& attributes, std::string& content)
{
	//sanity checks here please 
	addTagName(name, this);
	setNodeAttributes(ASTManager::parseattributes(attributes), this);
	ASTManager::addNodeChildrenFromContent(content, this);
	if (this->nodeAttributes.find("maxRequests") == this->nodeAttributes.end() || this->nodeAttributes["maxRequests"].find_first_not_of("0123456789") != std::string::npos) {
		std::cerr << "Error: maxRequests attribute is missing in RateLimitNode" << std::endl;
		return;
	}
	this->rate = std::stoi(this->nodeAttributes["maxRequests"]);
	this->time = this->nodeAttributes["per"];

}

bool RateLimitNode::beginLimit() {

	//std::this_thread::sleep_for();
	//continously check that the an ip address has not been 
	return true;
}

// adds one to the ip_address if it is already in memory, or creates a new std::pair with the ip_address and sets it to zero
void RateLimitNode::addNewIpaddress(const std::string& ip_address)
{
	
	//check that the ip address is not already in the map
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		this->ip_attempts_map[ip_address] += 1;
	}
	else {
		this->ip_attempts_map[ip_address] = 1;
	}
}

int RateLimitNode::getIpAttempts(const std::string& ip_address)
{
	//check if the ip address is in the map
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		return this->ip_attempts_map[ip_address];
	}
	return 0;
}

void RateLimitNode::removeIpaddress(std::string& ip_address)
{
	//remove the ip address from the map
	this->ip_attempts_map.erase(this->ip_attempts_map.find(ip_address));
}

bool RateLimitNode::isRateLimited(const std::string& ip_address){
	//check that `maxRequests` is exists as an attribute ... else use 100
	if(this->nodeAttributes.find("maxRequests") != this->nodeAttributes.end())
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		//we need to keep track of the time and check if the time is within the rate limit
		for (auto [key, value] : this->nodeAttributes) {
			std::cout << key << value << "\n";
		}
		if (this->ip_attempts_map[ip_address] >= this->rate) {
			return true;
		}
	}
	return false;
}

bool RateLimitNode::startCheck() {

	//std::thread worker(RateLimitNode::beginLimit);
	//worker.join();

	return true;
}

/*
void RateLimitNode::startCentralResetThread() {
	std::thread([this]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(1)); // or configurable

			std::lock_guard<std::mutex> lock(this->mutex);

			auto now = std::chrono::steady_clock::now();
			for (auto it = ipTimestamps.begin(); it != ipTimestamps.end(); ++it) {
				const std::string& ip = it->first;
				auto& [count, lastResetTime] = it->second;

				if (now - lastResetTime >= std::chrono::seconds(this->perSeconds)) {
					it->second = { 0, now }; // reset count and update timer
				}
			}
		}
		}).detach();
}
*/
