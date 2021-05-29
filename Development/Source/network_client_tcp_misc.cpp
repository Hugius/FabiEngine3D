#define WIN32_LEAN_AND_MEAN

#include "network_client_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkClientTCP::isRunning()
{
	return _isRunning;
}

bool NetworkClientTCP::isConnectedToServer()
{
	return _isConnectedToServer;
}

const vector<NetworkMessage>& NetworkClientTCP::getPendingMessages()
{
	return _pendingMessages;
}

void NetworkClientTCP::sendMessage(const string& content)
{
	if (_isConnectedToServer)
	{
		// Add a semicolon to indicate end of this message
		string messageContent = content + ';';
		auto sendStatusCode = send(_serverSocketID, messageContent.c_str(), static_cast<int>(messageContent.size()), 0);

		// Check if sending went well
		if (sendStatusCode == SOCKET_ERROR)
		{
			if ((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED)) // Lost connection with host
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
	else
	{
		Logger::throwWarning("Networking client cannot send message to server!");
	}
}

void NetworkClientTCP::_initiateConnection()
{
	// Create socket for connecting to the server
	_serverSocketID = socket(_addressInfo->ai_family, _addressInfo->ai_socktype, _addressInfo->ai_protocol);
	if (_serverSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client startup (socket create) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = std::async(std::launch::async, &NetworkClientTCP::_connectWithServer, this, _serverSocketID, _addressInfo);
}

void NetworkClientTCP::_closeConnection()
{
	closesocket(_serverSocketID);
	_isConnectedToServer = false;
}

int NetworkClientTCP::_connectWithServer(SOCKET serverSocketID, addrinfo* addressInfo)
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

tuple<int, string, int> NetworkClientTCP::_waitForServerMessage(SOCKET serverSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::MAX_MESSAGE_BYTES];
	int bufferLength = NetworkUtils::MAX_MESSAGE_BYTES;
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