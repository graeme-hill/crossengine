#include "WebSocketServer.hpp"

#include <websocketpp/common/cpp11.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

BEGIN_XE_NAMESPACE

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;

class WebSocketServer::Impl
{
public:
	Impl(
		unsigned port,
		std::function<void(std::weak_ptr<void>)> onConnected,
		std::function<void(std::weak_ptr<void>)> onDisconnected,
		std::function<void(std::weak_ptr<void>, Blob)> onMessage);
	void send(Blob blob, std::weak_ptr<void> conn);

private:
	void onMessage(server *s, websocketpp::connection_hdl hdl, message_ptr msg);
	void onOpen(websocketpp::connection_hdl hdl);
	void onClose(websocketpp::connection_hdl hdl);

	std::function<void(std::weak_ptr<void>)> _onConnectedCallback;
	std::function<void(std::weak_ptr<void>)> _onDisconnectedCallback;
	std::function<void(std::weak_ptr<void>, Blob)> _onMessageCallback;

	server _server;
};

WebSocketServer::Impl::Impl(
	unsigned port,
	std::function<void(std::weak_ptr<void>)> onConnected,
	std::function<void(std::weak_ptr<void>)> onDisconnected,
	std::function<void(std::weak_ptr<void>, Blob)> onMessage) :
	_onConnectedCallback(onConnected),
	_onDisconnectedCallback(onDisconnected),
	_onMessageCallback(onMessage)
{
	try
	{
		// Set logging settings
		_server.set_access_channels(websocketpp::log::alevel::all);
		_server.clear_access_channels(
			websocketpp::log::alevel::frame_payload);

		// Initialize Asio
		_server.init_asio();

		// Register our message handler
		_server.set_message_handler(bind(
			&WebSocketServer::Impl::onMessage, this, &_server, ::_1, ::_2));

		// Register connection handlers so we can keep track of them
		_server.set_open_handler(bind(
			&WebSocketServer::Impl::onOpen, this, ::_1));
		_server.set_close_handler(bind(
			&WebSocketServer::Impl::onClose, this, ::_1));

		// Listen on port 9002
		_server.listen(9002);

		// Start the server accept loop
		_server.start_accept();

		// Start the ASIO io_service run loop
		_server.run();
	}
	catch (websocketpp::exception const &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "other exception" << std::endl;
	}
}

void WebSocketServer::Impl::onMessage(
	server *s, websocketpp::connection_hdl hdl, message_ptr msg)
{
	auto dataString = msg->get_payload();
	Blob blob(
		reinterpret_cast<const uint8_t *>(dataString.data()),
		dataString.size());
	_onMessageCallback(hdl, blob);
}

void WebSocketServer::Impl::onOpen(websocketpp::connection_hdl hdl)
{
	_onConnectedCallback(hdl);
}

void WebSocketServer::Impl::onClose(websocketpp::connection_hdl hdl)
{
	_onDisconnectedCallback(hdl);
}

void WebSocketServer::Impl::send(Blob blob, std::weak_ptr<void> conn)
{
	websocketpp::lib::error_code err;

	_server.send(
		conn,
		blob.dataPtr(),
		blob.size(),
		websocketpp::frame::opcode::binary,
		err);

	if (err)
	{
		std::cout << "Error sending message: " << err.message() << std::endl;
	}
}

WebSocketServer::WebSocketServer(
	unsigned port,
	std::function<void(std::weak_ptr<void>)> onConnected,
	std::function<void(std::weak_ptr<void>)> onDisconnected,
	std::function<void(std::weak_ptr<void>, Blob)> onMessage) :
	_impl(std::make_unique<WebSocketServer::Impl>(
		port, onConnected, onDisconnected, onMessage))
{ }

WebSocketServer::~WebSocketServer() = default;

void WebSocketServer::send(Blob blob, std::weak_ptr<void> conn)
{
	_impl->send(blob, conn);
}

END_XE_NAMESPACE
