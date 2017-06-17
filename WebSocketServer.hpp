#pragma once

#include "Util.hpp"
#include <memory>
#define ASIO_STANDALONE

BEGIN_XE_NAMESPACE

class WebSocketServer
{
public:
	WebSocketServer(unsigned port);
	~WebSocketServer();

private:
	class Impl;
	std::unique_ptr<Impl> _impl;
};

END_XE_NAMESPACE
