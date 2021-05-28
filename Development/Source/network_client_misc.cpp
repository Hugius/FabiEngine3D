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
	return (_receivedMessage != nullptr);
}

bool NetworkClient::isConnected()
{
	return _isConnectedToServer;
}

const shared_ptr<NetworkMessage> NetworkClient::getPendingMessage()
{
	if (_receivedMessage == nullptr)
	{
		Logger::throwWarning("Cannot retrieve network message: no message pending!");
		return nullptr;
	}
	else
	{
		return _receivedMessage;
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
	_connectionThread = std::async(std::launch::async, &NetworkClient::_connectWithServer, this, _serverSocketID, _addressInfo);
}

void NetworkClient::_closeConnection()
{
	closesocket(_serverSocketID);
	_isConnectedToServer = false;
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

tuple<int, string, int> NetworkClient::_waitForServerMessage(SOCKET serverSocketID)
{
	// Retrieve bytes & size
	char buffer[MAX_MESSAGE_BYTES];
	int bufferLength = MAX_MESSAGE_BYTES;
	auto receiveResult = recv(serverSocketID, buffer, bufferLength, 0);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, string(buffer, receiveResult), WSAGetLastError());
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, "", WSAGetLastError());
	}
}