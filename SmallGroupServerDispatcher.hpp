#pragma once

#include "Util.hpp"
#include "SmallGroupConnectionManager.hpp"
#include "Blob.hpp"

BEGIN_XE_NAMESPACE

class SmallGroupServerDispatcher
{
public:
	SmallGroupServerDispatcher(
		SmallGroupConnectionManager &manager,
		std::weak_ptr<void> conn,
		std::function<void(Blob, std::weak_ptr<void>)> sendFunc);
	JoinResult joinGroup(int groupId);
	void broadcast(Blob blob);
	void forward(Blob blob);
	void reply(Blob blob);

private:
	SmallGroupConnectionManager &_manager;
	std::weak_ptr<void> _conn;
	std::function<void(Blob, std::weak_ptr<void>)> _sendFunc;
};

END_XE_NAMESPACE
