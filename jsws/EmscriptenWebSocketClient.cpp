#include "EmscriptenWebSocketClient.hpp"

BEGIN_XE_NAMESPACE

EmscriptenWebSocketClient::EmscriptenWebSocketClient()
{ }

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	std::string uri,
	std::function<void(Blob)> onMessage)
{ }

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	EmscriptenWebSocketClient &&other)
{ }

EmscriptenWebSocketClient &EmscriptenWebSocketClient::operator=(
	EmscriptenWebSocketClient &&other)
{
	return *this;
}

void EmscriptenWebSocketClient::send(Blob blob)
{ }

bool EmscriptenWebSocketClient::isConnected()
{
	return false;
}

EmscriptenWebSocketClient::~EmscriptenWebSocketClient()
{ }

END_XE_NAMESPACE
