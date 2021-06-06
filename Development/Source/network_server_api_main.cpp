#define WIN32_LEAN_AND_MEAN

#include "network_server_api.hpp"
#include "logger.hpp"

#include <winsock2.h>
#include <ws2tcpip.h>

NetworkServerAPI::NetworkServerAPI() :
	_connectionSocketID(INVALID_SOCKET),
	_udpMessageSocketID(INVALID_SOCKET)
{

}

NetworkServerAPI::~NetworkServerAPI()
{
	if (_isRunning)
	{
		stop();
	}
}

void NetworkServerAPI::start(unsigned int customMaxClientCount)
{
	// Must not be running
	if (_isRunning)
	{
		Logger::throwWarning("Trying to start networking server: already running!");
		return;
	}

	// Check if custom client count is not too high
	if ((customMaxClientCount > NetworkUtils::MAX_CLIENT_COUNT) || (customMaxClientCount <= 0))
	{
		Logger::throwWarning("Trying to start networking server: invalid maximum client count!");
		return;
	}

	// Compose TCP address info hints
	addrinfo tcpHints = addrinfo();
	ZeroMemory(&tcpHints, sizeof(tcpHints));
	tcpHints.ai_family = AF_INET; // Ipv4 address
	tcpHints.ai_socktype = SOCK_STREAM; // Streaming socket
	tcpHints.ai_protocol = IPPROTO_TCP; // TCP protocol
	tcpHints.ai_flags = AI_PASSIVE; // Flag to indicate the current machines's IPV4 should be used

	// Compose UDP address info hints
	addrinfo udpHints = addrinfo();
	ZeroMemory(&udpHints, sizeof(udpHints));
	udpHints.ai_family = AF_INET; // Ipv4 address
	udpHints.ai_socktype = SOCK_DGRAM; // Datagram socket
	udpHints.ai_protocol = IPPROTO_UDP; // UDP protocol
	udpHints.ai_flags = AI_PASSIVE; // Flag to indicate the current machines's IPV4 should be used

	// Create TCP address info
	addrinfo* tcpAddressInfo = nullptr;
	auto tcpInfoStatusCode = getaddrinfo(nullptr, NetworkUtils::SERVER_PORT.c_str(), &tcpHints, &tcpAddressInfo);
	if (tcpInfoStatusCode != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", tcpInfoStatusCode);
		return;
	}

	// Create UDP address info
	addrinfo* udpAddressInfo = nullptr;
	auto udpInfoStatusCode = getaddrinfo(nullptr, NetworkUtils::SERVER_PORT.c_str(), &udpHints, &udpAddressInfo);
	if (udpInfoStatusCode != 0)
	{
		Logger::throwError("Network server startup (address info) failed with error code: ", udpInfoStatusCode);
		return;
	}

	// Create socket for listening to client connection requests
	_connectionSocketID = socket(tcpAddressInfo->ai_family, tcpAddressInfo->ai_socktype, tcpAddressInfo->ai_protocol);
	if (_connectionSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking server startup (TCP socket create) failed with error code: ", WSAGetLastError());
	}

	// Create socket for listening to client connection requests
	_udpMessageSocketID = socket(udpAddressInfo->ai_family, udpAddressInfo->ai_socktype, udpAddressInfo->ai_protocol);
	if (_udpMessageSocketID == INVALID_SOCKET)
	{
		Logger::throwError("Networking server startup (UDP socket create) failed with error code: ", WSAGetLastError());
	}

	// Add options to the connection socket
	DWORD optionValue = 1;
	setsockopt(_connectionSocketID, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&optionValue), sizeof(optionValue));

	// Bind the TCP connection socket
	auto tcpBindStatusCode = bind(_connectionSocketID, tcpAddressInfo->ai_addr, static_cast<int>(tcpAddressInfo->ai_addrlen));
	if (tcpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server startup (TCP socket bind) failed with error code: ", WSAGetLastError());
	}

	// Bind the UDP connection socket
	auto udpBindStatusCode = bind(_udpMessageSocketID, udpAddressInfo->ai_addr, static_cast<int>(udpAddressInfo->ai_addrlen));
	if (udpBindStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server startup (TCP socket bind) failed with error code: ", WSAGetLastError());
	}

	// Enable listening for any incoming connection requests
	auto listenStatusCode = listen(_connectionSocketID, SOMAXCONN);
	if (listenStatusCode == SOCKET_ERROR)
	{
		Logger::throwError("Networking server startup (TCP socket listen) failed with error code: ", WSAGetLastError());
	}

	// Spawn a thread for accepting incoming connection requests
	_connectionThread = std::async(std::launch::async, &NetworkServerAPI::_waitForClientConnection, this, _connectionSocketID);

	// Spawn a thread for any incoming UDP messages
	_udpMessageThread = std::async(std::launch::async, &NetworkServerAPI::_waitForClientMessageUDP, this, _udpMessageSocketID);

	// Address infos not needed anymore
	freeaddrinfo(tcpAddressInfo);
	freeaddrinfo(udpAddressInfo);

	// Server is now operable
	_customMaxClientCount = customMaxClientCount;
	_isRunning = true;

	// Logging
	Logger::throwInfo("Started network server!");
}

void NetworkServerAPI::stop()
{
	// Must be running first
	if (!_isRunning)
	{
		Logger::throwWarning("Trying to stop networking server: not running!");
		return;
	}

	// Close TCP connection socket
	closesocket(_connectionSocketID);

	// Close UDP message socket
	closesocket(_udpMessageSocketID);

	// Delete all connected clients
BEGIN:
	for (const auto& socketID : _clientSocketIDs)
	{
		_disconnectClient(socketID);
		goto BEGIN;
	}

	// Miscellaneous
	_pendingMessages.clear();
	_currentTcpMessageBuild = "";
	_connectionSocketID = INVALID_SOCKET;
	_udpMessageSocketID = INVALID_SOCKET;
	_customMaxClientCount = NetworkUtils::MAX_CLIENT_COUNT;
	_isRunning = false;

	// Logging
	Logger::throwInfo("Stopped network server!");
}