#include "EmscriptenWebSocketClient.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

uintptr_t makeJsFriendlyPointer(EmscriptenWebSocketClient *client)
{
	return reinterpret_cast<uintptr_t>(static_cast<void *>(client));
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient() : _connected(false)
{ }

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	std::string uri,
	std::function<void(Blob)> onMessage) :
	_onMessage(onMessage),
	_connected(false)
{
	auto me = makeJsFriendlyPointer(this);
	xews_connect(me, uri.c_str(), xews_onMessage, xews_onConnected);
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	EmscriptenWebSocketClient &&other) :
	_onMessage(other._onMessage),
	_connected(other._connected)
{
	auto newClient = makeJsFriendlyPointer(this);
	auto oldClient = makeJsFriendlyPointer(&other);
	xews_move(oldClient, newClient);
	other._onMessage = std::function<void(Blob)>();
	other._connected = false;
}

EmscriptenWebSocketClient &EmscriptenWebSocketClient::operator=(
	EmscriptenWebSocketClient &&other)
{
	return *this;
}

void EmscriptenWebSocketClient::send(Blob blob)
{ }

bool EmscriptenWebSocketClient::isConnected()
{
	return _connected;
}

EmscriptenWebSocketClient::~EmscriptenWebSocketClient()
{ }

END_XE_NAMESPACE

extern "C"
{
	void xews_onMessage(uintptr_t clientAddr)
	{
		auto client = reinterpret_cast<xe::EmscriptenWebSocketClient *>(
			clientAddr);

		//client._onMessage(
	}

	void xews_onConnected(uintptr_t clientAddr)
	{
		std::cout << "xews_onConnected\n";
		auto client = reinterpret_cast<xe::EmscriptenWebSocketClient *>(
			clientAddr);
		client->_connected = true;
	}
}
