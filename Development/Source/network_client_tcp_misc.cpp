#define WIN32_LEAN_AND_MEAN

#include "network_client_tcp.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

const bool NetworkClientTCP::isRunning()
{
	return _isRunning;
}

const bool NetworkClientTCP::isConnectingToServer()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve connecting status: not running!");
	}

	return _isConnectingToServer;
}

const bool NetworkClientTCP::isConnectedToServer()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve connection status: not running!");
	}

	return (_isConnectedToServer && _isAcceptedByServer);
}

const unsigned int NetworkClientTCP::getServerPing()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve server ping: not running!");
	}

	// Must be connected first
	if (!_isConnectedToServer)
	{
		Logger::throwWarning("Networking client tried to retrieve server ping: not connected!");
	}

	return _serverPing;
}

const vector<string>& NetworkClientTCP::getPendingMessages()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve pending messages not running!");
	}

	// Must be connected first
	if (!_isConnectedToServer)
	{
		Logger::throwWarning("Networking client tried to retrieve pending messages: not connected!");
	}

	return _pendingMessages;
}

void NetworkClientTCP::sendMessage(const string& content)
{
	_sendMessage(content, false);
}

void NetworkClientTCP::_sendMessage(const string& content, bool isReserved)
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to send message: not running!");
		return;
	}

	// Must be connected & accepted first
	if (!_isConnectedToServer && _isAcceptedByServer)
	{
		Logger::throwWarning("Networking client tried to send message: not running!");
		return;
	}

	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send message: cannot contain semicolons!");
		return;
	}

	// Validate message availability
	if (NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwWarning("Networking client tried to send message: \"" + content + "\" is reserved!");
		return;
	}

	// Add a semicolon to indicate end of this message
	string messageContent = content + ';';
	auto sendStatusCode = send(_serverSocketID, messageContent.c_str(), static_cast<int>(messageContent.size()), 0);

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		if ((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED)) // Lost connection with host
		{
			disconnectFromServer();
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking client send failed with error code: ", WSAGetLastError());
		}
	}
}

int NetworkClientTCP::_waitForServerConnection(SOCKET serverSocketID, addrinfo* addressInfo)
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

unsigned int NetworkClientTCP::_getCurrentMilliseconds()
{
	return static_cast<unsigned int>(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
}