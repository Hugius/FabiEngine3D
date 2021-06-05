#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

const bool NetworkClientAPI::isRunning()
{
	return _isRunning;
}

const bool NetworkClientAPI::isConnectingToServer()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve connecting status: not running!");
	}

	return _isConnectingToServer;
}

const bool NetworkClientAPI::isConnectedToServer()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve connection status: not running!");
	}

	return (_isConnectedToServer && _isAcceptedByServer);
}

const unsigned int NetworkClientAPI::getServerPing()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve server ping: not running!");
	}

	// Must be connected first
	if ((!_isConnectedToServer && _isAcceptedByServer))
	{
		Logger::throwWarning("Networking client tried to retrieve server ping: not connected!");
	}

	// Calculate average ping
	unsigned int totalPing = 0;
	for (const auto& ping : _serverPings)
	{
		totalPing += ping;
	}
	return (totalPing / static_cast<int>(_serverPings.size()));
}

const string NetworkClientAPI::getServerIP()
{
	return NetworkUtils::extractIP(_tcpServerSocketID);
}

const vector<NetworkServerMessage>& NetworkClientAPI::getPendingMessages()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to retrieve pending messages: not running!");
	}

	return _pendingMessages;
}

void NetworkClientAPI::sendMessageTCP(const string& content)
{
	_sendMessageTCP(content, false);
}

void NetworkClientAPI::sendMessageUDP(const string& content)
{
	//_sendMessageUDP(content);
}

bool NetworkClientAPI::_sendMessageTCP(const string& content, bool isReserved)
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to send TCP message: not running!");
		return false;
	}

	// Must be connected & accepted first
	if ((!_isConnectedToServer && _isAcceptedByServer))
	{
		Logger::throwWarning("Networking client tried to send TCP message: not connected!");
		return false;
	}

	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send TCP message: cannot contain semicolons!");
		return false;
	}

	// Validate message availability
	if (NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwWarning("Networking client tried to send TCP message: \"" + content + "\" is reserved!");
		return false;
	}

	// Add a semicolon to indicate end of this message
	string messageContent = content + ';';
	auto sendStatusCode = send(_tcpServerSocketID, messageContent.c_str(), static_cast<int>(messageContent.size()), 0);

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		if ((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED)) // Lost connection with host
		{
			disconnectFromServer();
			return false;
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking client TCP send failed with error code: ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkClientAPI::_sendMessageUDP(const string& serverIP, const string& serverPort, const string& content)
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to send UDP message: not running!");
		return false;
	}

	// Must be connected & accepted first
	if (!_isConnectedToServer && _isAcceptedByServer)
	{
		Logger::throwWarning("Networking client tried to send UDP message: not connected!");
		return false;
	}

	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send UDP message: cannot contain semicolons!");
		return false;
	}

	// Validate message availability
	if (NetworkUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking client tried to send UDP message: \"" + content + "\" is reserved!");
		return false;
	}

	// Compose socket address
	sockaddr_in targetAddress;
	targetAddress.sin_family = AF_INET;
	targetAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());
	targetAddress.sin_port = htons(stoi(serverPort));

	// Add a semicolon to indicate end of this message
	auto sendStatusCode = sendto(
		_udpServerSocketID, // UDP socket
		content.c_str(), // Message
		static_cast<int>(content.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&targetAddress), // Server address
		sizeof(targetAddress)); // Server address length

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking client send failed with error code: ", WSAGetLastError());
		if ((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED)) // Lost connection with host
		{
			disconnectFromServer();
			return false;
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking client UDP send failed with error code: ", WSAGetLastError());
		}
	}

	return true;
}

int NetworkClientAPI::_waitForServerConnection(SOCKET serverSocketID, const string& serverIP, const string& serverPort)
{
	// Compose socket address
	sockaddr_in targetAddress;
	targetAddress.sin_family = AF_INET;
	targetAddress.sin_port = htons(stoi(serverPort));
	targetAddress.sin_addr.s_addr = inet_addr(serverIP.c_str());

	// Try to connect to server
	auto connectStatusCode = connect(
		serverSocketID,
		reinterpret_cast<sockaddr*>(&targetAddress),
		sizeof(targetAddress));
	
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

tuple<int, int, long long, string> NetworkClientAPI::_waitForServerMessageTCP(SOCKET tcpServerSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::MAX_MESSAGE_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::MAX_MESSAGE_BYTES);
	auto receiveResult = recv(tcpServerSocketID, buffer, bufferLength, 0);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, long long, string, string, string> NetworkClientAPI::_waitForServerMessageUDP(SOCKET udpServerSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::MAX_MESSAGE_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::MAX_MESSAGE_BYTES);
	sockaddr_in sourceAddress;
	int sourceAddressLength;
	auto receiveResult = recvfrom(udpServerSocketID, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);
	auto IP = NetworkUtils::extractIP(sourceAddress);
	auto port = NetworkUtils::extractIP(sourceAddress);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult), IP, port);
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "", IP, port);
	}
}