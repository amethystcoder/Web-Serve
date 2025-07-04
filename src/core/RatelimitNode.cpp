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
	/*
		if (this->nodeAttributes.find("type") == this->nodeAttributes.end()) {
		//default is to use non threded version
		this->StartSynchronousLimiting();
		}
		else if (this->nodeAttributes["type"] == "central") {
			//start the central reset thread
			this->startCentralResetThread();
		}
		else if (this->nodeAttributes["type"] == "synchronous") {
			//start the synchronous limiting
			this->StartSynchronousLimiting();
		}
		else this->StartSynchronousLimiting();
	*/
	
	return true;
}

// adds one to the ip_address if it is already in memory, or creates a new std::pair with the ip_address and sets it to zero
void RateLimitNode::addNewIpaddress(const std::string& ip_address)
{
	
	//check that the ip address is not already in the map
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		this->ip_attempts_map[ip_address].first += 1;
	}
	else {
		this->ip_attempts_map[ip_address].first = 1;
	}
}

void RateLimitNode::removeIpaddress(std::string& ip_address)
{
	//remove the ip address from the map
	this->ip_attempts_map.erase(this->ip_attempts_map.find(ip_address));
}

int RateLimitNode::getIpAttempts(const std::string& ip_address)
{
	//check if the ip address is in the map
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		return this->ip_attempts_map[ip_address].first;
	}
	return 0;
}

//TODO: Check this function properly
bool RateLimitNode::isRateLimited(const std::string& ip_address){
	//check that `maxRequests` is exists as an attribute ... else use 100
	if(this->nodeAttributes.find("maxRequests") != this->nodeAttributes.end())
	if (this->ip_attempts_map.find(ip_address) != this->ip_attempts_map.end()) {
		//we need to keep track of the time and check if the time is within the rate limit
		if (this->ip_attempts_map[ip_address].second >= this->rate) {
			return true;
		}
	}
	return false;
}

/*
void RateLimitNode::StartSynchronousLimiting() {
	auto time_now = std::chrono::steady_clock::now();
	for(auto& [first, second]: this->ip_attempts_map){
		if (second.second + std::chrono::seconds(this->rate) < time_now) {
			second.first = 0; //reset the count
			second.second = time_now; //update the last reset time
		}
		else {
			second.first += 1; //increment the count
		}
	}
}

void RateLimitNode::startCentralResetThread() {
	std::thread([this]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::seconds(1));

			std::lock_guard<std::mutex> lock(this->attempts_mutex);

			auto now = std::chrono::steady_clock::now();
			for (auto it = this->ip_attempts_map.begin(); it != this->ip_attempts_map.end(); ++it) {
				const std::string& ip = it->first;
				auto& [count, lastResetTime] = it->second;

				if (now - lastResetTime >= std::chrono::seconds(this->rate)) {
					it->second = { 0, now }; // reset count and update timer
				}
			}
			//this->attempts_mutex.unlock();
		}
		}).detach();
}
*/


