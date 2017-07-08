#pragma once

#include "Util.hpp"
#include <unordered_map>
#include <unordered_set>
#include "StdExtensions.hpp"

BEGIN_XE_NAMESPACE

struct JoinResult
{
	bool success;
	uint8_t player;
};

struct Group
{
	int id;
	std::unordered_set<std::weak_ptr<void>> connections;
};

class SmallGroupConnectionManager
{
public:
	void addConnection(std::weak_ptr<void> conn);
	void removeConnection(std::weak_ptr<void> conn);
	JoinResult joinGroup(std::weak_ptr<void> conn, int groupId);

	std::unordered_set<std::weak_ptr<void>> *connectionsInGroup(
		std::weak_ptr<void> conn);

private:
	std::unordered_map<int, Group> _groups;
	std::unordered_map<std::weak_ptr<void>, int> _connections;
};

END_XE_NAMESPACE
