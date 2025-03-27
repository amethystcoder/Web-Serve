#ifndef RATELIMITNODE_H
#define RATELIMITNODE_H

#include <unordered_map>
#include "ast.h"


class RateLimitNode : public ASTreeNode
{
public:
	RateLimitNode();
	~RateLimitNode();

	void registernode(const std::string& name, const std::string& attributes, std::string& content);

private:
	std::string time;
	short unsigned int rate;
};

#endif // !RATELIMITNODE_H

