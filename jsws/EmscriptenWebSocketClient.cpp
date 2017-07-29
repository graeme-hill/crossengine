#include "EmscriptenWebSocketClient.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

int EmscriptenWebSocketClient::_instanceCount = 0;

uintptr_t makeJsFriendlyPointer(EmscriptenWebSocketClient *client)
{
	return reinterpret_cast<uintptr_t>(static_cast<void *>(client));
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient() :
	_connected(false),
	_instanceId(_instanceCount++)
{ }

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	std::string uri,
	std::function<void(Blob)> onMessage) :
	_onMessage(onMessage),
	_connected(false),
	_instanceId(_instanceCount++)
{
	auto me = makeJsFriendlyPointer(this);
	xews_connect(me, uri.c_str(), xews_onMessage, xews_onConnected);
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	EmscriptenWebSocketClient &&other) :
	_onMessage(other._onMessage),
	_connected(other._connected),
	_instanceId(_instanceCount++)
{
	auto newClient = makeJsFriendlyPointer(this);
	auto oldClient = makeJsFriendlyPointer(&other);
	xews_move(oldClient, newClient);
	other._onMessage = std::function<void(Blob)>();
	other._connected = false;
	other._instanceId = -1;
}

EmscriptenWebSocketClient &EmscriptenWebSocketClient::operator=(
	EmscriptenWebSocketClient &&other)
{
	_onMessage = other._onMessage;
	_connected = other._connected;
	_instanceId = other._instanceId;
	other._instanceId = -1;
	auto newClient = makeJsFriendlyPointer(this);
	auto oldClient = makeJsFriendlyPointer(&other);
	xews_move(oldClient, newClient);
	return *this;
}

void EmscriptenWebSocketClient::send(Blob blob)
{
	auto clientAddr = makeJsFriendlyPointer(this);
	xews_send(clientAddr, blob.dataPtr(), blob.size());
}

bool EmscriptenWebSocketClient::isConnected()
{
	return _connected;
}

EmscriptenWebSocketClient::~EmscriptenWebSocketClient()
{ }

END_XE_NAMESPACE

extern "C"
{
	void xews_onMessage(uintptr_t clientAddr, uintptr_t dataAddr, size_t size)
	{
		auto client = reinterpret_cast<xe::EmscriptenWebSocketClient *>(
			clientAddr);

		auto data = reinterpret_cast<uint8_t *>(dataAddr);

		client->_onMessage({ data, size });
	}

	void xews_onConnected(uintptr_t clientAddr)
	{
		xe::EmscriptenWebSocketClient *client =
			reinterpret_cast<xe::EmscriptenWebSocketClient *>(clientAddr);

		client->_connected = true;
	}
}
