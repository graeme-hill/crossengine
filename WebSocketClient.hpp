#pragma once

#define ASIO_STANDALONE
#include <string>
#include <memory>
#include "Util.hpp"

BEGIN_XE_NAMESPACE

class WebSocketClient
{
public:
	WebSocketClient(std::string uri);
	~WebSocketClient();

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

END_XE_NAMESPACE
