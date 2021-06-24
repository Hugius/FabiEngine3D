#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

bool NetworkClientAPI::_sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted)
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to send TCP message: not running!");
		return false;
	}

	// Must be connected & optionally accepted
	if (!_isConnectedToServer || !_isAcceptedByServer)
	{
		if (mustBeAccepted)
		{
			Logger::throwWarning("Networking client tried to send TCP message: not connected!");
			return false;
		}
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
	auto sendStatusCode = send(_connectionSocketID, message.c_str(), static_cast<int>(message.size()), 0);

	// Check if sending went well
	if (sendStatusCode == SOCKET_ERROR)
	{
		if ((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED)) // Lost connection with host
		{
			disconnectFromServer(mustBeAccepted);
			return false;
		}
		else // Something really bad happened
		{
			Logger::throwError("Networking client TCP send failed with error code: ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkClientAPI::_sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted)
{
	// Must be running
	if (!_isRunning)
	{
		Logger::throwWarning("Networking client tried to send UDP message: not running!");
		return false;
	}

	// Must be connected & optionally accepted
	if (!_isConnectedToServer || !_isAcceptedByServer)
	{
		if (mustBeAccepted)
		{
			Logger::throwWarning("Networking client tried to send UDP message: not connected!");
			return false;
		}
	}

	// Validate message semantics
	if (std::find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwWarning("Networking client tried to send UDP message: cannot contain semicolons!");
		return false;
	}
	else if (NetworkUtils::isMessageReserved(content) && !isReserved)
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
	auto socketAddress = NetworkUtils::composeSocketAddress(_serverIP, _serverPort);

	// Add a semicolon to separate username & content
	string message = _username + ';' + content;

	// Send message to server
	auto sendStatusCode = sendto(
		_udpMessageSocketID, // UDP socket
		message.c_str(), // Message content
		static_cast<int>(message.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&socketAddress), // Server address
		sizeof(socketAddress)); // Server address length

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
	auto socketAddress = NetworkUtils::composeSocketAddress(serverIP, serverPort);

	// Try to connect to server
	auto connectStatusCode = connect(
		serverSocketID,
		reinterpret_cast<sockaddr*>(&socketAddress),
		sizeof(socketAddress));
	
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

void NetworkClientAPI::_setupTCP()
{
	// Create TCP socket
	_connectionSocketID = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (_connectionSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client TCP socket create failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = std::async(std::launch::async, &NetworkClientAPI::_waitForServerConnection, this, _connectionSocketID, _serverIP, _serverPort);
}

void NetworkClientAPI::_setupUDP(const string& tcpPort)
{
	// Compose UDP address info hints
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_DGRAM; // Datagram socket
	hints.ai_protocol = IPPROTO_UDP; // UDP protocol
	hints.ai_flags = AI_PASSIVE; // Flag to indicate the current machines's IPV4 should be used
	
	// Create UDP address info
	addrinfo* addressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo(nullptr, tcpPort.c_str(), &hints, &addressInfo);
	if (udpInfoStatusCode != 0)
	{
		Logger::throwError("Networking client UDP address info failed with error code: ", udpInfoStatusCode);
		return;
	}

	// Create UDP socket
	_udpMessageSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if (_udpMessageSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking client UDP socket create failed with error code: ", WSAGetLastError());
	}

	// Bind UDP socket
	auto udpBindStatusCode = bind(_udpMessageSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if (udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking client UDP socket bind failed with error code: ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);
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

tuple<int, int, string, string, string> NetworkClientAPI::_receiveUdpMessage(SOCKET udpSocketID)
{
	// Data store
	char buffer[NetworkUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkUtils::UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	// Retrieve data
	auto receiveResult = recvfrom(udpSocketID, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);
	
	// Extract address
	auto IP = NetworkUtils::extractSocketAddressIP(&sourceAddress);
	auto port = NetworkUtils::extractSocketAddressPort(&sourceAddress);

	if (receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), IP, port);
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", IP, port);
	}
}