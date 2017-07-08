#include "SmallGroupServerDispatcher.hpp"

BEGIN_XE_NAMESPACE

SmallGroupServerDispatcher::SmallGroupServerDispatcher(
	SmallGroupConnectionManager &manager,
	std::weak_ptr<void> conn,
	std::function<void(Blob, std::weak_ptr<void>)> sendFunc) :
	_manager(manager),
	_conn(conn),
	_sendFunc(sendFunc)
{ }

JoinResult SmallGroupServerDispatcher::joinGroup(int groupId)
{
	return _manager.joinGroup(_conn, groupId);
}

void SmallGroupServerDispatcher::broadcast(Blob blob)
{
	auto connections = _manager.connectionsInGroup(_conn);
	if (connections != nullptr)
	{
		for (auto conn : *connections)
		{
			_sendFunc(blob, conn);
		}
	}
}

void SmallGroupServerDispatcher::forward(Blob blob)
{
	auto connections = _manager.connectionsInGroup(_conn);
	if (connections != nullptr)
	{
		for (auto conn : *connections)
		{
			if (conn != _conn)
			{
				_sendFunc(blob, conn);
			}
		}
	}
}

void SmallGroupServerDispatcher::reply(Blob blob)
{
	_sendFunc(blob, _conn);
}

END_XE_NAMESPACE
