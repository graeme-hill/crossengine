#include "WebSocketServer.hpp"

#include <websocketpp/common/cpp11.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <set>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

BEGIN_XE_NAMESPACE

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;

class WebSocketServer::Impl
{
public:
	Impl(unsigned port);

private:
	void onMessage(server *s, websocketpp::connection_hdl hdl, message_ptr msg);
	void onOpen(websocketpp::connection_hdl hdl);
	void onClose(websocketpp::connection_hdl hdl);
	std::set<
		websocketpp::connection_hdl,
		std::owner_less<websocketpp::connection_hdl>> _connections;
};

WebSocketServer::Impl::Impl(unsigned port)
{
	server echoServer;

	try
	{
		// Set logging settings
		echoServer.set_access_channels(websocketpp::log::alevel::all);
		echoServer.clear_access_channels(
			websocketpp::log::alevel::frame_payload);

		// Initialize Asio
		echoServer.init_asio();

		// Register our message handler
		echoServer.set_message_handler(bind(
			&WebSocketServer::Impl::onMessage, this, &echoServer, ::_1, ::_2));

		// Register connection handlers so we can keep track of them
		echoServer.set_open_handler(bind(
			&WebSocketServer::Impl::onOpen, this, ::_1));
		echoServer.set_close_handler(bind(
			&WebSocketServer::Impl::onClose, this, ::_1));

		// Listen on port 9002
		echoServer.listen(9002);

		// Start the server accept loop
		echoServer.start_accept();

		// Start the ASIO io_service run loop
		echoServer.run();
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
	std::cout << "got a message" << std::endl;

	// // check for a special command to instruct the server to stop listening so
	// // it can be cleanly exited.
	// if (msg->get_payload() == "stop-listening")
	// {
	// 	s->stop_listening();
	// 	return;
	// }

	try
	{
		for (auto conn : _connections)
		{
			s->send(conn, msg->get_payload(), msg->get_opcode());
		}
		//s->send(hdl, msg->get_payload(), msg->get_opcode());
	}
	catch (const websocketpp::lib::error_code &e)
	{
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}
}

void WebSocketServer::Impl::onOpen(websocketpp::connection_hdl hdl)
{
	_connections.insert(hdl);
}

void WebSocketServer::Impl::onClose(websocketpp::connection_hdl hdl)
{
	_connections.erase(hdl);
}

WebSocketServer::WebSocketServer(unsigned port) :
	_impl(std::make_unique<WebSocketServer::Impl>(port))
{ }

WebSocketServer::~WebSocketServer() = default;

END_XE_NAMESPACE
