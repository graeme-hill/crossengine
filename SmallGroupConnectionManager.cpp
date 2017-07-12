#include "SmallGroupConnectionManager.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

void SmallGroupConnectionManager::addConnection(std::weak_ptr<void> conn)
{
	_connections[conn] = -1;
}

void SmallGroupConnectionManager::removeConnection(std::weak_ptr<void> conn)
{
	auto groupId = _connections[conn];
	auto groupFindResult = _groups.find(groupId);
	if (groupFindResult != _groups.end())
	{
		auto &group = std::get<Group>(*groupFindResult);
		group.connections.erase(conn);
		if (group.connections.empty())
		{
			_groups.erase(group.id);
		}
	}
	_connections.erase(conn);
}

JoinResult SmallGroupConnectionManager::joinGroup(
	std::weak_ptr<void> conn, int groupId)
{
	JoinResult result;
	result.success = true;
	auto existingGroup = _groups.find(groupId);
	if (existingGroup != _groups.end())
	{
		result.player = static_cast<uint8_t>(
			std::get<Group>(*existingGroup).connections.size()) + 1;
		std::get<Group>(*existingGroup).connections.insert(conn);
	}
	else
	{
		result.player = 1;
		_groups[groupId] = { groupId, { conn } };
	}
	_connections[conn] = groupId;
	return result;
}

std::unordered_set<std::weak_ptr<void>> *
SmallGroupConnectionManager::connectionsInGroup(std::weak_ptr<void> conn)
{
	auto groupId = _connections[conn];
	auto existingGroup = _groups.find(groupId);
	if (existingGroup != _groups.end())
	{
		return &std::get<Group>(*existingGroup).connections;
	}
	else
	{
		return nullptr;
	}
}

END_XE_NAMESPACE
