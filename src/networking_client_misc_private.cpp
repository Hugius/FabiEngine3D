#define WIN32_LEAN_AND_MEAN

#include "networking_client.hpp"
#include "logger.hpp"
#include "tools.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

using std::launch;

bool NetworkingClient::_sendTcpMessage(const string& content, bool isReserved, bool mustBeAccepted)
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::1");
	}

	// Must be connected & optionally accepted
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::2");
	}

	// Validate message content
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::3");
	}
	if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::4");
	}
	if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingClient::_sendTcpMessage::5");
	}

	// Add a semicolon to indicate end of this message
	string message = (content + ';');

	// Send message to server
	auto sendStatusCode = send(_tcpSocket, message.c_str(), static_cast<int>(message.size()), 0);

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
			Logger::throwError("NetworkingClient::_sendTcpMessage::6 ---> ", WSAGetLastError());
		}
	}

	return true;
}

bool NetworkingClient::_sendUdpMessage(const string& content, bool isReserved, bool mustBeAccepted) const
{
	// Must be running
	if(!_isRunning)
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::1");
	}

	// Must be connected & optionally accepted
	if(!_isConnectedToServer || (!_isAcceptedByServer && mustBeAccepted))
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::2");
	}

	// Validate message semantics
	if(find(content.begin(), content.end(), ';') != content.end())
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::3");
	}
	else if(NetworkingUtils::isMessageReserved(content) && !isReserved)
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::4");
	}
	else if(content.size() > NetworkingUtils::MAX_MESSAGE_CHARACTERS)
	{
		Logger::throwError("NetworkingClient::_sendUdpMessage::5");
	}

	// Compose socket address
	auto socketAddress = NetworkingUtils::composeSocketAddress(_serverIP, _serverPort);

	// Add a semicolon to separate username & content
	string message = (_username + ';' + content);

	// Send message to server
	auto sendStatusCode = sendto(
		_udpSocket, // UDP socket
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
			Logger::throwError("NetworkingClient::_sendUdpMessage::6 ---> ", WSAGetLastError());
		}
	}

	return true;
}

int NetworkingClient::_waitForServerConnection(SOCKET socket, const string& serverIP, const string& serverPort) const
{
	// Compose socket address
	auto socketAddress = NetworkingUtils::composeSocketAddress(serverIP, serverPort);

	// Try to connect to server
	auto connectStatusCode = connect(
		socket,
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

void NetworkingClient::_setupTcp()
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
		Logger::throwError("NetworkingClient::_setupTCP::1 ---> ", tcpInfoStatusCode);
		return;
	}

	// Create socket
	_tcpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_tcpSocket == INVALID_SOCKET)
	{
		Logger::throwError("NetworkingClient::_setupTCP::2 ---> ", WSAGetLastError());
	}

	// Bind socket
	auto tcpBindStatusCode = bind(_tcpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(tcpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkingClient::_setupTCP::3 ---> ", WSAGetLastError());
	}

	// Spawn a thread for connecting to the server
	_connectionThread = async(launch::async, &NetworkingClient::_waitForServerConnection, this, _tcpSocket, _serverIP, _serverPort);
}

void NetworkingClient::_setupUdp()
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
		Logger::throwError("NetworkingClient::_setupUDP::1 ---> ", udpInfoStatusCode);
		return;
	}

	// Create socket
	_udpSocket = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
	if(_udpSocket == INVALID_SOCKET)
	{
		Logger::throwError("NetworkingClient::_setupUDP::2 ----> ", WSAGetLastError());
	}

	// Bind socket
	auto udpBindStatusCode = bind(_udpSocket, addressInfo->ai_addr, static_cast<int>(addressInfo->ai_addrlen));
	if(udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("NetworkingClient::_setupUDP::3 ---> ", WSAGetLastError());
	}

	// Address info not needed anymore
	freeaddrinfo(addressInfo);
}

tuple<int, int, long long, string> NetworkingClient::_waitForTcpMessage(SOCKET socket) const
{
	// Retrieve bytes & size
	char buffer[NetworkingUtils::TCP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::TCP_BUFFER_BYTES);
	auto receiveResult = recv(socket, buffer, bufferLength, 0);

	if(receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), string(buffer, receiveResult));
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), Tools::getTimeSinceEpochMS(), "");
	}
}

tuple<int, int, string, string, string> NetworkingClient::_receiveUdpMessage(SOCKET socket) const
{
	// Data store
	char buffer[NetworkingUtils::UDP_BUFFER_BYTES];
	int bufferLength = static_cast<int>(NetworkingUtils::UDP_BUFFER_BYTES);
	sockaddr_in sourceAddress = sockaddr_in();
	int sourceAddressLength = sizeof(sourceAddress);

	// Retrieve data
	auto receiveResult = recvfrom(socket, buffer, bufferLength, 0, reinterpret_cast<sockaddr*>(&sourceAddress), &sourceAddressLength);

	// Extract address
	auto IP = NetworkingUtils::extractAddressIP(&sourceAddress);
	auto port = NetworkingUtils::extractAddressPort(&sourceAddress);

	if(receiveResult > 0) // Message received correctly
	{
		return make_tuple(receiveResult, WSAGetLastError(), string(buffer, receiveResult), IP, port);
	}
	else // Something else happened
	{
		return make_tuple(receiveResult, WSAGetLastError(), "", IP, port);
	}
}