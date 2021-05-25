#define WIN32_LEAN_AND_MEAN

#include "network_server.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkServer::isRunning()
{
	return _isRunning;
}

SOCKET NetworkServer::_waitForClientConnection(SOCKET listenSocketID)
{
	return accept(listenSocketID, NULL, NULL);
}

pair<int, string> NetworkServer::_waitForClientMessage(SOCKET clientSocketID)
{
	char buffer[3];
	int bufferLength = 3;

	auto statusCode = recv(clientSocketID, buffer, bufferLength, 0);

	return std::make_pair(statusCode, string(buffer));
}