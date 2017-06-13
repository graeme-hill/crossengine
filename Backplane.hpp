#pragma once

#include <vector>
#include "flatbuffers/flatbuffers.h"

BEGIN_XE_NAMESPACE

template <typename TMessage, typename THandler>
class Backplane
{
public:
	Backplane() { }
	Backplane(Backplane const &) = delete;
	Backplane(Backplane &&) = delete;
	void post(flatbuffers::DetachedBuffer buffer);
	void receive(THandler &handler);

private:
	std::vector<flatbuffers::DetachedBuffer> _pending;
};

template <typename TMessage, typename THandler>
void Backplane<TMessage, THandler>::post(flatbuffers::DetachedBuffer buffer)
{
	_pending.push_back(std::move(buffer));
}

template <typename TMessage, typename THandler>
void Backplane<TMessage, THandler>::receive(THandler &handler)
{
	for (auto &buffer : _pending)
	{
		handler.receiveBuffer(buffer);
	}
	_pending.clear();
}

END_XE_NAMESPACE
