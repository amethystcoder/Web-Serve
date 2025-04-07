#include "RatelimitNode.h"
#include <iostream>

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
	this->rate = std::stoi(this->nodeAttributes["rate"]);
	this->time = this->nodeAttributes["time"];
	std::cout << "RateLimitNode: " << name << " registered with rate: " << this->rate << " and time: " << this->time << std::endl;

}

bool RateLimitNode::beginLimit() {

	//std::this_thread::sleep_for();
	//continously check that the an ip address has not been 
	return true;
}

// adds one to the ip_address if it is already in memory, or creates a new std::pair with the ip_address and sets it to zero
void RateLimitNode::addNewIpaddress(const std::string& ip_address)
{
	//if the ip already is in the map, add one to the 
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end())
		this->ip_attempts_map[ip_address] = 0;
	else
		this->ip_attempts_map[ip_address]++;
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
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		//we need to keep track of the time and check if the time is within the rate limit
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
