#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkClientAPI::_sendTcpMessage(const string& content, bool isReserved)
{
	// Must be connected & accepted
	if (!_isConnectedToServer && _isAcceptedByServer)
	{
		Logger::throwWarning("Networking client tried to send TCP message: not connected!");
		return false;
	}

	// Validate message content
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send TCP message: cannot contain semicolons!");
		return false;
	}
	else if (NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwWarning("Networking client tried to send TCP message: \"" + content + "\" is reserved!");
		return false;
	}
	else if (content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to send TCP message: maximum character amount exceeded!");
		return false;
	}

	// Add a semicolon to indicate end of this message
	string message = content + ';';

	// Send message to server
	auto sendStatusCode = send(_tcpSocketID, message.c_str(), static_cast<int>(message.size()), 0);

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

bool NetworkClientAPI::_sendUdpMessage(const string& content)
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
	else if (NetworkUtils::isMessageReserved(content))
	{
		Logger::throwWarning("Networking client tried to send UDP message: \"" + content + "\" is reserved!");
		return false;
	}
	else if (content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwWarning("Networking client tried to send UDP message: maximum character amount exceeded!");
		return false;
	}

	// Compose socket address
	sockaddr_in targetAddress = sockaddr_in();
	targetAddress.sin_family = AF_INET;
	targetAddress.sin_addr.s_addr = inet_addr(_serverIP.c_str());
	targetAddress.sin_port = htons(stoi(_serverPort));

	// Add a semicolon to separate username & content
	string message = _username + ';' + content;

	// Send message to server
	auto sendStatusCode = sendto(
		_udpSocketID, // UDP socket
		message.c_str(), // Message content
		static_cast<int>(message.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&targetAddress), // Server address
		sizeof(targetAddress)); // Server address length

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking client UDP send failed with error code: ", WSAGetLastError());
	}

	return true;
}

int NetworkClientAPI::_waitForServerConnection(SOCKET serverSocketID, const string& serverIP, const string& serverPort)
{
	// Compose socket address
	sockaddr_in targetAddress = sockaddr_in();
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

tuple<int, int, long long, string> NetworkClientAPI::_waitForTcpMessage(SOCKET tcpSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::TCP_BUFFER_BYTES);
	auto receiveResult = recv(tcpSocketID, buffer, bufferLength, 0);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, long long, string> NetworkClientAPI::_receiveUdpMessage(SOCKET udpSocketID)
{
	// Retrieve bytes & size
	char buffer[NetworkUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::UDP_BUFFER_BYTES);
	auto receiveResult = recvfrom(udpSocketID, buffer, bufferLength, 0, nullptr, nullptr);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}