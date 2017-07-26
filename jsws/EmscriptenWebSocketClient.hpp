#pragma once

#include <string>
#include <memory>
#include "Util.hpp"
#include "Blob.hpp"

extern "C"
{
	extern void xews_connect(
		uintptr_t clientAddr,
		const char *,
		void (*onMessage)(uintptr_t, uintptr_t, size_t),
		void (*onConnected)(uintptr_t));

	extern void xews_send(
		uintptr_t clientAddr, const uint8_t *data, size_t size);

	extern void xews_close(uintptr_t clientAddr);

	extern void xews_move(uintptr_t oldClientAddr, uintptr_t newClientAddr);

	void xews_onMessage(uintptr_t clientAddr, uintptr_t dataAddr, size_t size);

	void xews_onConnected(uintptr_t clientAddr);
}

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
	EmscriptenWebSocketClient(EmscriptenWebSocketClient &other) = delete;
	EmscriptenWebSocketClient &operator=(EmscriptenWebSocketClient &&other);
	void send(Blob blob);
	bool isConnected();
	~EmscriptenWebSocketClient();

private:
	void setConnected();
	std::function<void(Blob)> _onMessage;
	bool _connected;
	int _instanceId;
	int _number = 24;

	static int _instanceCount;
	friend void ::xews_onMessage(
		uintptr_t clientAddr, uintptr_t dataAddr, size_t size);
	friend void ::xews_onConnected(uintptr_t clientAddr);
};

END_XE_NAMESPACE
