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

struct Group
{
	int id;
	std::unordered_set<websocketpp::connection_hdl> connections;
};

class WebSocketServer::Impl
{
public:
	Impl(unsigned port);

private:
	void onMessage(server *s, websocketpp::connection_hdl hdl, message_ptr msg);
	void onOpen(websocketpp::connection_hdl hdl);
	void onClose(websocketpp::connection_hdl hdl);
	void joinGroup(websocketpp::connection_hdl hdl, int groupId);

	std::unordered_map<int, Group> _groups;
	std::unordered_map<websocketpp::connection_hdl, int> _connections;
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

	// try
	// {
	// 	for (auto conn : _connections)
	// 	{
	// 		s->send(conn, msg->get_payload(), msg->get_opcode());
	// 	}
	// 	//s->send(hdl, msg->get_payload(), msg->get_opcode());
	// }
	// catch (const websocketpp::lib::error_code &e)
	// {
	// 	std::cout << "Echo failed because: " << e
	// 		<< "(" << e.message() << ")" << std::endl;
	// }
}

void WebSocketServer::Impl::joinGroup(
	websocketpp::connection_hdl hdl, int groupId)
{
	auto existingGroup = _groups.find(groupId);
	if (existingGroup != _groups.end())
	{
		std::get<Group>(*existingGroup).connections.insert(hdl);
	}
	else
	{
		_groups[groupId] = { groupId, { hdl } };
	}
	_connections[hdl] = groupId;
}

void WebSocketServer::Impl::onOpen(websocketpp::connection_hdl hdl)
{
	_connections[hdl] = -1;
}

void WebSocketServer::Impl::onClose(websocketpp::connection_hdl hdl)
{
	auto groupId = _connections[hdl];
	auto groupFindResult = _groups.find(groupId);
	if (groupFindResult != _groups.end())
	{
		auto &group = std::get<Group>(*groupFindResult);
		group.connections.erase(hdl);
		if (group.connections.empty())
		{
			_groups.erase(group.id);
		}
	}
	_connections.erase(hdl);
}

WebSocketServer::WebSocketServer(unsigned port) :
	_impl(std::make_unique<WebSocketServer::Impl>(port))
{ }

WebSocketServer::~WebSocketServer() = default;

END_XE_NAMESPACE
