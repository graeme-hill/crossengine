#pragma once

#include "Util.hpp"
#include "SmallGroupConnectionManager.hpp"
#include "WebSocketServer.hpp"

BEGIN_XE_NAMESPACE

template <typename THandler>
class SmallGroupWebSocketConfig
{
public:
	using Backend = WebSocketServer;
	using Handler = THandler;
	using ConnectionManager = SmallGroupConnectionManager;
	using Dispatcher = SmallGroupServerDispatcher;
};

END_XE_NAMESPACE
