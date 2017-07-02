#pragma once

#include <vector>
#include "flatbuffers/flatbuffers.h"
#include "WebSocketClient.hpp"

BEGIN_XE_NAMESPACE

template <typename THandler>
class MessageBus
{
public:
	MessageBus();
	MessageBus(MessageBus const &) = delete;
	MessageBus(MessageBus &&) = delete;
	void post(flatbuffers::DetachedBuffer buffer);
	void postLocal(flatbuffers::DetachedBuffer buffer);
	void receive(THandler &handler);
	void connect(std::string uri);

private:
	std::vector<flatbuffers::DetachedBuffer> _pending;
	WebSocketClient _client;
};

template <typename THandler>
MessageBus<THandler>::MessageBus()
{ }

template <typename THandler>
void MessageBus<THandler>::post(flatbuffers::DetachedBuffer buffer)
{
	_client.send(buffer);
	_pending.push_back(std::move(buffer));
}

template <typename THandler>
void MessageBus<THandler>::postLocal(flatbuffers::DetachedBuffer buffer)
{
	_pending.push_back(std::move(buffer));
}

template <typename THandler>
void MessageBus<THandler>::receive(THandler &handler)
{
	for (auto &buffer : _pending)
	{
		handler.receiveBuffer(buffer);
	}
	_pending.clear();
}

template <typename THandler>
void MessageBus<THandler>::connect(std::string uri)
{
	_client = WebSocketClient(uri);
}

END_XE_NAMESPACE
