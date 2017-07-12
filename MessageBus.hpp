#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include "flatbuffers/flatbuffers.h"
#include "WebSocketClient.hpp"
#include "Blob.hpp"

BEGIN_XE_NAMESPACE

template <typename THandler>
class MessageBus
{
public:
	MessageBus();
	MessageBus(MessageBus const &) = delete;
	MessageBus(MessageBus &&) = delete;
	void post(Blob blob);
	void postLocal(Blob blob);
	void receive(THandler &handler);
	void receiveIf(
		THandler &handler, std::function<bool(const Blob &)> predicate);
	void connect(std::string uri);

private:
	std::vector<Blob> _pending;
	WebSocketClient _client;
	std::mutex _clientMutex;
};

template <typename THandler>
MessageBus<THandler>::MessageBus()
{
	std::cout << "msg bus created\n";
}

template <typename THandler>
void MessageBus<THandler>::post(Blob blob)
{
	std::cout << "post()\n";
	std::lock_guard<std::mutex> lock(_clientMutex);
	if (_client.isConnected())
	{
		std::cout << "connected = true\n";
		_client.send(blob);
	}
	_pending.push_back(blob);
}

template <typename THandler>
void MessageBus<THandler>::postLocal(Blob blob)
{
	std::lock_guard<std::mutex> lock(_clientMutex);
	_pending.push_back(blob);
}

template <typename THandler>
void MessageBus<THandler>::receive(THandler &handler)
{
	receiveIf(handler, [](const Blob &blob) { return true; });
}

template <typename THandler>
void MessageBus<THandler>::receiveIf(
	THandler &handler, std::function<bool(const Blob &)> predicate)
{
	for (auto &blob : _pending)
	{
		if (predicate(blob))
		{
			handler.receiveBlob(blob);
		}
	}
	_pending.clear();
}

template <typename THandler>
void MessageBus<THandler>::connect(std::string uri)
{
	std::lock_guard<std::mutex> lock(_clientMutex);
	_client = WebSocketClient(uri, [this](Blob blob)
	{
		std::cout << "WebSocketClient callback dealie\n";
		postLocal(blob);
	});
}

END_XE_NAMESPACE
