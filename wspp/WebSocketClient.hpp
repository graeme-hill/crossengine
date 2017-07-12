#pragma once

#define ASIO_STANDALONE
#include <string>
#include <memory>
#include "Util.hpp"
#include "Blob.hpp"

BEGIN_XE_NAMESPACE

class WebSocketClient
{
public:
	WebSocketClient();
	WebSocketClient(
		std::string uri,
		std::function<void(Blob)> onMessage);
	WebSocketClient(WebSocketClient const &other) = delete;
	WebSocketClient(WebSocketClient &&other);
	WebSocketClient &operator=(WebSocketClient &&other);
	void send(Blob blob);
	bool isConnected();
	~WebSocketClient();

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

END_XE_NAMESPACE
