#define WIN32_LEAN_AND_MEAN

#include "network_client.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkClient::isRunning()
{
	return _isRunning;
}

bool NetworkClient::isMessagePending()
{
	return !_receivedMessageQueue.empty();
}

void NetworkClient::loadNextMessage()
{
	if (_receivedMessageQueue.empty())
	{
		Logger::throwWarning("Cannot load next network message: no messages pending!");
	}
	else
	{
		_receivedMessageQueue.erase(_receivedMessageQueue.begin());
	}
}

const shared_ptr<NetworkMessage> NetworkClient::getPendingMessage()
{
	if (_receivedMessageQueue.empty())
	{
		Logger::throwWarning("Cannot retrieve network message: no messages pending!");
		return nullptr;
	}
	else
	{
		return _receivedMessageQueue.front();
	}
}
int NetworkClient::_connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo)
{
	auto connectStatusCode = connect(serverSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));

	if (connectStatusCode == SOCKET_ERROR)
	{
		return WSAGetLastError();;
	}
	else
	{
		return 0;
	}
}