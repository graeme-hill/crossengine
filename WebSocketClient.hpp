#pragma once

#define ASIO_STANDALONE
#include <string>
#include <memory>
#include "Util.hpp"
#include "flatbuffers/flatbuffers.h"

BEGIN_XE_NAMESPACE

class WebSocketClient
{
public:
	WebSocketClient();
	WebSocketClient(std::string uri);
	WebSocketClient(WebSocketClient const &other) = delete;
	WebSocketClient(WebSocketClient &&other);
	WebSocketClient &operator=(WebSocketClient &&other);
	void send(flatbuffers::DetachedBuffer const &blob);
	bool isConnected();
	~WebSocketClient();

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

END_XE_NAMESPACE
