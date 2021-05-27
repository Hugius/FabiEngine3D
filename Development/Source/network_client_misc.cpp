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

bool NetworkClient::isConnectedToServer()
{
	return _isConnectedToServer;
}

void NetworkClient::loadNextPendingMessage()
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

void NetworkClient::sendMessage(const string& content)
{
	auto sendStatusCode = send(_serverSocketID, content.c_str(), static_cast<int>(content.size()), 0);

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAECONNRESET) // Lost connection with host
		{
			_closeConnection();
			_initiateConnection();
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking client send failed with error code: ", WSAGetLastError());
		}
	}
}

void NetworkClient::_initiateConnection()
{
	// Create socket for connecting to the server
	_serverSocketID = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
	if (_serverSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_spawnConnectionThread();
}

void NetworkClient::_closeConnection()
{
	closesocket(_serverSocketID);
	_isConnectedToServer = false;
}

void NetworkClient::_spawnConnectionThread()
{
	_connectionThread = std::async(std::launch::async, &NetworkClient::_connectWithServer, this, _serverSocketID, _addressInfo);
}

int NetworkClient::_connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo)
{
	auto connectStatusCode = connect(serverSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	
	// Check if connection attempt went well
	if (connectStatusCode == SOCKET_ERROR)
	{
		return WSAGetLastError();
	}
	else
	{
		return 0;
	}
}