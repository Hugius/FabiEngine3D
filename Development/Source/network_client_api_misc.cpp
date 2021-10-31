#define WIN32_LEAN_AND_MEAN

#include "network_client_api.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

bool NetworkClientAPI::_sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::_sendTcpMessage::1");
	}

	// Must be connected & optionally accepted
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkClientAPI::_sendTcpMessage::2");
	}

	// Validate message content
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkClientAPI::_sendTcpMessage::3");
	}
	if(NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkClientAPI::_sendTcpMessage::4");
	}
	if(content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkClientAPI::_sendTcpMessage::5");
	}

	// Add a semicolon to indicate end of this message
	string message = (content + ';');

	// Send message to server
	auto sendStatusCode = send(_tcpSocketID, message.c_str(), static_cast<int>(message.size()), 0);

	// Check if sending went well
	if(sendStatusCode == SOCKET_ERROR)
	{
		if((WSAGetLastError() == WSAECONNRESET) || (WSAGetLastError() == WSAECONNABORTED)) // Lost connection with host
		{
			disconnectFromServer(mustBeAccepted);
			return false;
		}
		else if(WSAGetLastError() == WSAENOBUFS) // Buffer full
		{
			Logger::throwWarning("Networking client is sending too many TCP messages!");
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkClientAPI::_sendTcpMessage::6 ---> ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkClientAPI::_sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkClientAPI::_sendUdpMessage::1");
	}

	// Must be connected & optionally accepted
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkClientAPI::_sendUdpMessage::2");
	}

	// Validate message semantics
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkClientAPI::_sendUdpMessage::3");
	}
	else if(NetworkUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkClientAPI::_sendUdpMessage::4");
	}
	else if(content.size() > NetworkUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkClientAPI::_sendUdpMessage::5");
	}

	// Compose socket address
	auto socketAddress = NetworkUtils::composeSocketAddress(_serverIP, _serverPort);

	// Add a semicolon to separate username & content
	string message = _username + ';' + content;

	// Send message to server
	auto sendStatusCode = sendto(
		_udpSocketID, // UDP socket
		message.c_str(), // Message content
		static_cast<int>(message.size()), // Message size
		0, // Flags
		reinterpret_cast<sockaddr*>(&socketAddress), // Server address
		sizeof(socketAddress)); // Server address length

	// Check if sending went well
	if(sendStatusCode == SOCKET_ERROR)
	{
		if(WSAGetLastError() == WSAENOBUFS) // Buffer full
		{
			Logger::throwWarning("Networking client is sending too many UDP messages!");
		}
		else // Something really bad happened
		{
			Logger::throwError("NetworkClientAPI::_sendUdpMessage::6 ---> ", WSAGetLastError());
		}
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

	// Check if connection failed
	if(connectStatusCode == SOCKET_ERROR)
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
	// Compose address info hints
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_STREAM; // Streaming socket
	hints.ai_protocol = IPPROTO_TCP; // TCP protocol

	// Create address info
	addrinfo* addressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(tcpInfoStatusCode != 0)
	{
		Logger::throwError("NetworkClientAPI::_setupTCP::1 ---> ", tcpInfoStatusCode);
		return;
	}

	// Create socket
	_tcpSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_tcpSocketID == INVALID_SOCKET)
	{
		Logger::throwError("NetworkClientAPI::_setupTCP::2 ---> ", WSAGetLastError());
	}

	// Bind socket
	auto tcpBindStatusCode = bind(_tcpSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkClientAPI::_setupTCP::3 ---> ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = async(launch::async, &NetworkClientAPI::_waitForServerConnection, this, _tcpSocketID, _serverIP, _serverPort);
}

void NetworkClientAPI::_setupUDP()
{
	// Compose address info hints
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET; // Ipv4 address
	hints.ai_socktype = SOCK_DGRAM; // Datagram socket
	hints.ai_protocol = IPPROTO_UDP; // UDP protocol

	// Create address info
	addrinfo* addressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo("0.0.0.0", "0", &hints, &addressInfo);
	if(udpInfoStatusCode != 0)
	{
		Logger::throwError("NetworkClientAPI::_setupUDP::1 ---> ", udpInfoStatusCode);
		return;
	}

	// Create socket
	_udpSocketID = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_udpSocketID == INVALID_SOCKET)
	{
		Logger::throwError("NetworkClientAPI::_setupUDP::2 ----> ", WSAGetLastError());
	}

	// Bind socket
	auto udpBindStatusCode = bind(_udpSocketID, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkClientAPI::_setupUDP::3 ---> ", WSAGetLastError());
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

	if(receiveResult > 0) // Message received correctly
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
	auto IP = NetworkUtils::extractAddressIP(&sourceAddress);
	auto port = NetworkUtils::extractAddressPort(&sourceAddress);

	if(receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), IP, port);
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", IP, port);
	}
}