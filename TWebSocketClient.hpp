#pragma once

#include "Util.hpp"

#ifdef PLATFORM_WEBSOCKETPP
#include "wspp/WebSocketClient.hpp"
BEGIN_XE_NAMESPACE
typedef WebSocketClient TWebSocketClient;
END_XE_NAMESPACE
#endif

#ifdef PLATFORM_WEB
#include "jsws/EmscriptenWebSocketClient.hpp"
BEGIN_XE_NAMESPACE
typedef EmscriptenWebSocketClient TWebSocketClient;
END_XE_NAMESPACE
#endif
