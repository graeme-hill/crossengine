#include "EmscriptenWebSocketClient.hpp"
#include <iostream>

BEGIN_XE_NAMESPACE

int EmscriptenWebSocketClient::_instanceCount = 0;

uintptr_t makeJsFriendlyPointer(EmscriptenWebSocketClient *client)
{
	std::cout << "makeJsFriendlyPointer client: " << client << std::endl;
	return reinterpret_cast<uintptr_t>(static_cast<void *>(client));
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient() :
	_connected(false),
	_instanceId(_instanceCount++)
{
	std::cout << "empty ctor\n";
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	std::string uri,
	std::function<void(Blob)> onMessage) :
	_onMessage(onMessage),
	_connected(false),
	_instanceId(_instanceCount++)
{
	std::cout << "main ctor\n";
	auto me = makeJsFriendlyPointer(this);
	xews_connect(me, uri.c_str(), xews_onMessage, xews_onConnected);
}

EmscriptenWebSocketClient::EmscriptenWebSocketClient(
	EmscriptenWebSocketClient &&other) :
	_onMessage(other._onMessage),
	_connected(other._connected),
	_instanceId(_instanceCount++)
{
	std::cout << "move ctor: " << _connected << std::endl;
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
	std::cout << "operator=\n";
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
	std::cout << "isConnected() -> " << _connected << " instanceId -> " << _instanceId << std::endl;
	return _connected;
}

EmscriptenWebSocketClient::~EmscriptenWebSocketClient()
{
	std::cout << "dtor " << _instanceId << std::endl;
}

END_XE_NAMESPACE

extern "C"
{
	void xews_onMessage(uintptr_t clientAddr, uintptr_t dataAddr, size_t size)
	{
		std::cout << "xews_onMessage dataAddr: " << dataAddr << std::endl;
		auto client = reinterpret_cast<xe::EmscriptenWebSocketClient *>(
			clientAddr);

		auto data = reinterpret_cast<uint8_t *>(dataAddr);

		std::cout << "BYTES: ";
		for (unsigned i = 0; i < size; i++)
		{
			std::cout << static_cast<unsigned int>(data[i]) << ", ";
		}
		std::cout << std::endl;

		client->_onMessage({ data, size });
	}

	void xews_onConnected(uintptr_t clientAddr)
	{
		std::cout << "xews_onConnected clientAddr: " << clientAddr << "\n";
		xe::EmscriptenWebSocketClient *client =
			reinterpret_cast<xe::EmscriptenWebSocketClient *>(clientAddr);

		std::cout << "---" << client->_number << "---\n";
		std::cout << client->_instanceId << std::endl;
		std::cout << client->_instanceId << std::endl;
		std::cout << client->_instanceId << std::endl;
		std::cout << client->_instanceId << std::endl;
		std::cout << client->_instanceId << std::endl;
		std::cout << client->_instanceId << std::endl;
		std::cout << client->_instanceId << std::endl;
		std::cout << "---" << client->_number << "---\n";
		client->_connected = true;
		//std::cout << "_connected=" << client->_connected << " instance=" << client->_instanceId << std::endl;
	}
}
