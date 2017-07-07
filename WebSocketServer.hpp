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

namespace std
{
	inline bool operator==(
		const std::weak_ptr<void> &a, const std::weak_ptr<void> &b)
	{
		return true;
	}

	template <>
	struct hash<std::weak_ptr<void>>
	{
		std::size_t operator()(const std::weak_ptr<void> &val) const
		{
			auto shared = val.lock();
			if (shared)
			{
				return std::hash<decltype(shared)>()(shared);
			}
			else
			{
				return 0;
			}
		}
	};
}
