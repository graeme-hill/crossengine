#pragma once

#include "Util.hpp"
#include "Blob.hpp"
#include <memory>
#define ASIO_STANDALONE

BEGIN_XE_NAMESPACE

class WebSocketServer
{
public:
	WebSocketServer(
		unsigned port,
		std::function<void(std::weak_ptr<void>)> onConnected,
		std::function<void(std::weak_ptr<void>)> onDisconnected,
		std::function<void(std::weak_ptr<void>, Blob)> onMessage);
	~WebSocketServer();
	void send(Blob blob, std::weak_ptr<void> conn);

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

END_XE_NAMESPACE
