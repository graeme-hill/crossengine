#include "WebSocketServer.hpp"

#include <websocketpp/common/cpp11.hpp>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>

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
		s->send(hdl, msg->get_payload(), msg->get_opcode());
	}
	catch (const websocketpp::lib::error_code &e)
	{
		std::cout << "Echo failed because: " << e
			<< "(" << e.message() << ")" << std::endl;
	}
}

WebSocketServer::WebSocketServer(unsigned port) :
	_impl(std::make_unique<WebSocketServer::Impl>(port))
{ }

WebSocketServer::~WebSocketServer() = default;

END_XE_NAMESPACE
