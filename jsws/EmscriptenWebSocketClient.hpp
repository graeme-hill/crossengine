#pragma once

#include <string>
#include <memory>
#include "Util.hpp"
#include "Blob.hpp"

BEGIN_XE_NAMESPACE

class EmscriptenWebSocketClient
{
public:
	EmscriptenWebSocketClient();
	EmscriptenWebSocketClient(
		std::string uri,
		std::function<void(Blob)> onMessage);
	EmscriptenWebSocketClient(EmscriptenWebSocketClient const &other) = delete;
	EmscriptenWebSocketClient(EmscriptenWebSocketClient &&other);
	EmscriptenWebSocketClient &operator=(EmscriptenWebSocketClient &&other);
	void send(Blob blob);
	bool isConnected();
	~EmscriptenWebSocketClient();

// private:
// 	class Impl;
// 	std::unique_ptr<Impl> _impl;
};

END_XE_NAMESPACE
