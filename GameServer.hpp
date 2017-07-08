#pragma once

#include "Util.hpp"

BEGIN_XE_NAMESPACE

template <typename TConfig>
class GameServer
{
public:
	GameServer(unsigned port);

private:
	std::function<void(std::weak_ptr<void>)> connectedFunc();
	std::function<void(std::weak_ptr<void>)> disconnectedFunc();
	std::function<void(std::weak_ptr<void>, Blob)>
		receiveMessageFunc();

	void onConnected(std::weak_ptr<void> conn);
	void onDisconnected(std::weak_ptr<void> conn);
	void onMessage(std::weak_ptr<void> conn, Blob blob);

	typename TConfig::Backend _backend;
	typename TConfig::Handler _handler;
	typename TConfig::ConnectionManager _connManager;
};

template <typename TConfig>
GameServer<TConfig>::GameServer(unsigned port) :
	_backend(port, connectedFunc(), disconnectedFunc(), receiveMessageFunc())
{ }

template <typename TConfig>
std::function<void(std::weak_ptr<void>)>
GameServer<TConfig>::connectedFunc()
{
	return [this](std::weak_ptr<void> conn)
	{
		onConnected(conn);
	};
}

template <typename TConfig>
std::function<void(std::weak_ptr<void>)>
GameServer<TConfig>::disconnectedFunc()
{
	return [this](std::weak_ptr<void> conn)
	{
		onDisconnected(conn);
	};
}

template <typename TConfig>
std::function<void(std::weak_ptr<void>, Blob)>
GameServer<TConfig>::receiveMessageFunc()
{
	return [this](std::weak_ptr<void> conn, Blob blob)
	{
		onMessage(conn, blob);
	};
}

template <typename TConfig>
void GameServer<TConfig>::onConnected(std::weak_ptr<void> conn)
{
	_connManager.addConnection(conn);
	//_handler.onConnected(conn);
}

template <typename TConfig>
void GameServer<TConfig>::onDisconnected(std::weak_ptr<void> conn)
{
	//_handler.onDisconnected(conn);
	_connManager.removeConnection(conn);
}

template <typename TConfig>
void GameServer<TConfig>::onMessage(std::weak_ptr<void> conn, Blob blob)
{
	typename TConfig::Dispatcher dispatcher(
		_connManager, conn, [this](Blob blob, std::weak_ptr<void> conn)
		{
			_backend.send(blob, conn);
		});

	_handler.onMessage(blob, dispatcher);
}

template <typename TConfig>
inline void serve(unsigned port)
{
	GameServer<TConfig> server(port);
}

END_XE_NAMESPACE
