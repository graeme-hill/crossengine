#include "WebSocketClient.hpp"

#include <websocketpp/common/cpp11.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

BEGIN_XE_NAMESPACE

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

class WebSocketClient::Impl
{
public:
	Impl(std::string uri);

private:
	void onMessage(client *c, websocketpp::connection_hdl hdl, message_ptr msg);
};

WebSocketClient::Impl::Impl(std::string uri)
{
	websocketpp::client<websocketpp::config::asio_client> c;

	try {
		// Set logging to be pretty verbose (everything except message payloads)
		c.set_access_channels(websocketpp::log::alevel::all);
		c.clear_access_channels(websocketpp::log::alevel::frame_payload);

		// Initialize ASIO
		c.init_asio();

		// Register our message handler
		c.set_message_handler(
			bind(&WebSocketClient::Impl::onMessage, this, &c, ::_1, ::_2));

		websocketpp::lib::error_code ec;
		auto con = c.get_connection(uri, ec);
		if (ec)
		{
			std::cout << "could not create connection because: "
				<< ec.message() << std::endl;
			return;
		}

		// Note that connect here only requests a connection. No network messages are
		// exchanged until the event loop starts running in the next line.
		c.connect(con);

		// Start the ASIO io_service run loop
		// this will cause a single connection to be made to the server. c.run()
		// will exit when this connection is closed.
		c.run();
	} catch (websocketpp::exception const & e) {
		std::cout << e.what() << std::endl;
	}
}

void WebSocketClient::Impl::onMessage(
	client *c, websocketpp::connection_hdl hdl, message_ptr msg)
{
	std::cout << "on_message called with hdl: " << hdl.lock().get()
			  << " and message: " << msg->get_payload()
			  << std::endl;

	websocketpp::lib::error_code ec;

	c->send(hdl, msg->get_payload(), msg->get_opcode(), ec);
	if (ec)
	{
		std::cout << "Echo failed because: " << ec.message() << std::endl;
	}
}

WebSocketClient::WebSocketClient(std::string uri) :
	_impl(std::make_unique<WebSocketClient::Impl>(uri))
{ }

WebSocketClient::~WebSocketClient() = default;

END_XE_NAMESPACE
